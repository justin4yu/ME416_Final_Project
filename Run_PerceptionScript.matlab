function StartPython()
%#codegen

% Include the C standard library at the top level
coder.cinclude('<stdlib.h>');

persistent scriptStarted;

if isempty(scriptStarted)
    scriptStarted = true;
    % Execute the system command
    coder.ceval('system', cstring('python3 /home/oj/Perception/tag_tracker_udp.py &'));
end
end

function y = cstring(str)
y = [str, char(0)];
end
