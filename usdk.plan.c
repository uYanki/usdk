typedef struct {
    struct {
        f32 rate;
        f32 times;
    } acc, dec;

    f32 out, tgt;

    void* arg;

} plan_t;

bool plan_isok(plan_t* plan)
{
    return plan->out == plan->tgt;
}

// 线性
f32 plan_doit(plan_t* plan)
{
    f32 delta = plan->tgt - plan->out;

    if (delta > 0) {
        plan->out += plan->acc.rate;
        ++(plan->acc.times);
        if (plan->out > plan->tgt) {
            plan->out = plan->tgt;
        }
    } else if (delta < 0) {
        plan->out -= plan->dec.rate;
        ++(plan->dec.times);
        if (plan->out < plan->tgt) {
            plan->out = plan->tgt;
        }
    }

    return plan->out;
}

