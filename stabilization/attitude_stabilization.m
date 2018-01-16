clear;
a = .75 %My alpha value
scaler_16g = 16 * 9.8 * .000029; %adjusts to m/s^2. I think.

%% Sample Data Aquisition
sampledata = csvread('LPF_sampledata.csv');
samples = sampledata(:,1);
accel_x = sampledata(:,2)+365; %bias
accel_y = sampledata(:,3)+20; %bias
accel_z = sampledata(:,4)-1580; %bias
gyro_x = sampledata(:,5);
gyro_y = sampledata(:,6);
gyro_z = sampledata(:,7);

%% Acceleromter
%Scale the values.
accel_x = accel_x * scaler_16g;
% accel_y = accel_y * scaler_16g;
% accel_z = accel_z * scaler_16g;

phi_accel = atan(accel_y ./ accel_z); %%this... may be in radians
theta_accel = asin(accel_x / 9.8);
%phi_accel = ... currently unused.

figure(1)
plot(samples, accel_x, '-', samples, accel_y, '-', samples, accel_z, '-');
axis tight;
legend("x","y","z");


figure(2)
subplot(2,1,1)
plot(samples, phi_accel, '-', samples, theta_accel, '-');
axis tight;
subplot(2,1,2)
plot(samples, LPF(phi_accel,a), '-', samples, LPF(theta_accel,a), '-');
axis tight;
