function robot = buildRobot()
    d2 = 187.908;
    L(1) = Link('d', 67.281, 'a', 0, 'alpha', pi/2, 'qlim', [-pi pi]);
    L(2) = Link('prismatic', 'offset', 375.781, 'a', 0, 'alpha', -pi/2, ...
               'theta', pi/2, 'qlim', [0 d2]);
    L(3) = Link('d', 0, 'a', 78.2975, 'alpha', -pi/2, 'qlim', [-pi 0]);
    robot = SerialLink(L, 'name', 'Christopher');
end