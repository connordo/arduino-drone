clear;
%% Sample Data Aquisition
sampledata = csvread('LPF_sampledata.csv');
samples = sampledata(:,1);
accel_x = sampledata(:,2)+365; %bias
accel_y = sampledata(:,3)+20; %bias
accel_z = sampledata(:,4)-1580;
gyro_x = sampledata(:,5);
gyro_y = sampledata(:,6);
gyro_z = sampledata(:,7);

a = .75 %My alpha value
zscaler = .00620253 % 9.8 mps / 1580 (resting average zaccel reading)

%% Acclerometer -- Low Pass Filter

figure(1);
subplot(4,1,1);
plot(samples, accel_x, '-', samples, accel_y, '-', samples, accel_z);
title("Raw Accelerometer Data");
xlabel("Samples");
ylabel("Values");
legend('X-axis','Y-axis','Z-axis');
axis tight;

subplot(4,1,2);
plot(samples, LPF(accel_x, a), '-', samples, LPF(accel_y, a), '-', samples, LPF(accel_z, a), '-');
legend('X-axis','Y-axis','Z-axis');
title("Low Filtered Accelerometer Data");
xlabel("Samples");
ylabel("Values");
axis tight;

%% Gyroscope -- High Pass Filter

%
subplot(4,1,3);
plot(samples, gyro_x, '-', samples, gyro_y, '-', samples, gyro_z);
legend('X-axis','Y-axis','Z-axis');
title("Raw Gyro Data");
xlabel("Samples");
ylabel("Values");
axis tight;

% phi_accel = atan(accel_y_lpf/accel_z_lpf);
subplot(4,1,4);
plot(samples, HPF(gyro_x, a), '-', samples, HPF(gyro_y, a), '-', samples, HPF(gyro_z, a), '-');
legend('X-axis','Y-axis','Z-axis');
title("High Filtered Gyro Data");
xlabel("Samples");
ylabel("Values");
axis tight;

%% Other Crap

figure(2);
phi_accel = atan(accel_y./accel_x);%What's wrong with this?
phi_gyro = samples;
phi_gyro = phi_gyro * 0;
phi_gyro(1) = gyro_y(1);
for i = 2:length(samples)
    phi_gyro(i) = phi_gyro(i-1) + gyro_y(i);
end


subplot (3,1,1);
plot(samples, accel_x, '-', samples, accel_y, '-', samples, accel_z);
subplot(3,1,2);
plot(samples, phi_accel);
subplot(3,1,3)
plot(samples, LPF(phi_accel, a));

figure(3);
zero_line = samples;
zero_line = zero_line * 0;

subplot(2,1,1);
plot(samples, phi_gyro, '-', samples, gyro_y, '-')
hold on;
plot(samples, zero_line, '.');
title("Gyroscope raw and Integral");
legend("Integral","Raw Data");
xlabel("samples");
ylabel("values");

subplot(2,1,2);
plot(samples, HPF(phi_gyro, a), '-');
title("Gyroscope HPF");
legend("Integral","Raw Data");
xlabel("samples");
ylabel("values");