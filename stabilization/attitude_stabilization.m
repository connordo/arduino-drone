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

%% Acceleromter

phi_accel = atan(accel_y./accel_z); %%this... may be in radians
theta_accel = asin(accel_x, 9.8);
%phi_accel = ... currently unused.

figure(1)
subplot(2,1,1)
