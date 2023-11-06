
f32 b[1024] = {0};
f32 buff[15];

int main()
{
    int n = 15;

    avg_fltr_t fltr;

    NotchFilter_UpdateCoeff(&NotchFilter, 0.00614 * 2, 0.00614, 1, 1);

    SecondOrderFilter_t foFltrBuf = {.a[0] = 0, .a[1] = 0.9, .b[0] = 0.05, .b[1] = 0.05};
    nOrderFilter_t      foFltr    = CreateSecondOrderFilter(&foFltrBuf);

    avg_fltr_init(&fltr, buff, 100);

    avg_fltr(a, b, 1024, n);

    FILE* f = fopen("./s.csv", "w+");

    fprintf(f, "a,b,c,d,e,f\n");

    for (u16 i = 0; i < 1024; ++i)
    {
        fprintf(f, "%f,%f,%f,%f,%f,%f,%f\n", org[i], (a[i]), (b[i]), NotchFilter_Handler(&NotchFilter, a[i]), avg_fltr_proc(&fltr, a[i]), nOrderFilter_Handler(&foFltr, a[i]));
        // fprintf(f, "%d,%d\n", (int) (a[i] * 1000), (int) (b[i] * 1000));
    }

    fclose(f);
}
