%Zad4
p_0 = [9, 0.14, 0.05, 11];

data = readmatrix('MNUB_24L_P3_dane32.csv');
tdata = data(:,1);
xdata = data(:,2);
ydata = data(:,3);
p_opt = fminsearch(@(p) FunJ(p, tdata, xdata, ydata), p_0);

function J = FunJ(p_current, tdata, xdata, ydata)
    p1 = p_current(1);
    p2 = p_current(2);
    p3 = p_current(3);
    p4 = p_current(4);

    xy0(1)=xdata(1);
    xy0(2)=ydata(1);

    % Rozwiązanie równania różniczkowego
    [t, xy] = ode45(@(t, xy) LotVol(t, xy, p1, p2, p3, p4), tdata, xy0);

    J = sum((xdata - xy(:,1)).^2) + sum((ydata - xy(:,2)).^2);
end

%funkcje
function dxydt = LotVol(t, xy, p1, p2, p3, p4)
    dxydt=zeros(2,1);
    dxydt(1) = p1*xy(1) - p2*xy(1)*xy(2);
    dxydt(2) = p3*xy(1)*xy(2) - p4*xy(2);
end