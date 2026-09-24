clear s
freeports = serialportlist("available") % Shows available serial ports
%Choose which port to use for Arduino (proabably best to hardcode)
ports = "/dev/ttyACM0";%freeports(2)

%Generate calibration curve
calib = [547;418;337;257;219;194;169;136;112;110;55;44;17];
realval = 20:10:140;
realval = realval.';
fit_func = fit(calib,realval,'poly2');

% Arduino Setup Stuff
baudrate = 115200;
s = serialport("COM6",baudrate);

%Format data visualization
full_data = zeros(90);
colormap(jet);
axis square;

%initialize a timeout in case MATLAB cannot connect to the arduino
timeout = 0;
% main loop to read data from the Arduino, then display it%
while timeout < 20 % % check if data was received %
    while s.NumBytesAvailable > 0
     
        % reset timeout
        timeout = 0;
        
        %data was received, convert it into array of integers
        Reading = sscanf(readline(s),'%f',[1 3]);
        
        %Cap readings that are out of range
        if Reading(3) < 30
            Reading(3) = 30;
        end
        
        %Store data in matrix
        full_data(90-Reading(1)+1,90-Reading(2)+1) = fit_func(Reading(3));
        
        %Visualize the data
        image(full_data)    
    end
    pause(0.5);
    timeout = timeout + 1;
end
