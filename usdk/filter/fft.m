
N = length(sample);
matlab_fft = figure;
yfreq = fft(y)/N ;
% yfreq = fftshift(y)/N ;
f = (0:N-1)*10/N;
yfreq =yfreq*2;
plot(f(1:N/2),abs(yfreq(1:N/2)));