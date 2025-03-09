p1=9;
p2=0.14;
p3=0.05;
p4=11;
tspan=[0 1];
xy0(1)=450;
xy0(2)=20;

%Zad1
[t, xy]=ode45(@(t, xy) LotVol(t,xy,p1,p2,p3,p4), tspan, xy0);

figure(1);
plot(t, xy(:,1), '-o', 'DisplayName', 'x');
grid on;
hold on;
plot(t, xy(:,2), '-x', 'DisplayName', 'y');
legend;
xlabel('Czas');
ylabel('Wartość');

%Zad2
h=0.005;
t2 = 0:h:1;
xy2 = zeros(2, length(t2));
xy2(:,1) = xy0;
xy2=openeul(t2,xy2,p1,p2,p3,p4,h);
xy3=closeeul(t2,xy2,p1,p2,p3,p4,h);
xy4=Heun(t2,xy2,p1,p2,p3,p4,h);
xy5=AdamsMoul(t2,xy2,p1,p2,p3,p4,h);

figure(2);
plot(t2, xy2(1,:), '-o', 'DisplayName', 'x');
grid on;
hold on;
plot(t2, xy2(2,:), '-x', 'DisplayName', 'y');
legend;
xlabel('Czas');
ylabel('Wartość');

figure(3);
plot(t2, xy3(1,:), '-o', 'DisplayName', 'x');
grid on;
hold on;
plot(t2, xy3(2,:), '-x', 'DisplayName', 'y');
grid on;
legend;
xlabel('Czas');
ylabel('Wartość');

figure(4);
plot(t2, xy4(1,:), '-o', 'DisplayName', 'x');
grid on;
hold on;
plot(t2, xy4(2,:), '-x', 'DisplayName', 'y');
legend;
xlabel('Czas');
ylabel('Wartość');
hold off;

figure(5);
plot(t2, xy5(1,:), '-o', 'DisplayName', 'x');
grid on;
hold on;
plot(t2, xy5(2,:), '-x', 'DisplayName', 'y');
legend;
xlabel('Czas');
ylabel('Wartość');
hold off;

%Zad3
[t, xyref]=ode45(@(t, xyref) LotVol(t,xyref,p1,p2,p3,p4), t2, xy0, odeset('RelTol', 1e-8, 'AbsTol', 1e-12));
sigmaOpenEuly=norm(xyref(:,2)-xy2(2,:)')/norm(xyref(:,2));
sigmaCloseEuly=norm(xyref(:,2)-xy3(2,:)')/norm(xyref(:,2));
sigmaHeuny=norm(xyref(:,2)-xy4(2,:)')/norm(xyref(:,2));
sigmaAMy=norm(xyref(:,2)-xy5(2,:)')/norm(xyref(:,2));

%Zad4
xy2z4 = zeros(2, length(t2));
xy2z4(:,1) = xy0;
allsigmaOpenEuly=zeros(19,1);
allsigmaCloseEuly=zeros(19,1);
allsigmaHeuny=zeros(19,1);
allsigmaAMy=zeros(19,1);
hv = zeros(19,1);

figure(6);
grid on;
labels = {'Otwarty Euler', 'Zamknięty Euler', 'Heun', 'Adams-Moulton'};

for k=1:19
    if k<=10
        h=10^(-4)*k;
    else
        h=10^(-3)*(k-9);
    end
    hv(k)=h;
    t2 = 0:h:1;
    xy2z4 = zeros(2, length(t2));
    xy2z4(:,1) = xy0;
    xy3z4=xy2z4;
    xy4z4=xy2z4;
    xy5z4=xy2z4;

    [t, xyref]=ode45(@(t, xyref) LotVol(t,xyref,p1,p2,p3,p4), t2, xy0, odeset('RelTol', 1e-8, 'AbsTol', 1e-12));
    xy2z4=openeul(t2,xy2z4,p1,p2,p3,p4,h);
    xy3z4=closeeul(t2,xy2z4,p1,p2,p3,p4,h);
    xy4z4=Heun(t2,xy2z4,p1,p2,p3,p4,h);
    xy5z4=AdamsMoul(t2,xy2z4,p1,p2,p3,p4,h);
    allsigmaOpenEuly(k)=norm(xyref(:,2)-xy2z4(2,:)')/norm(xyref(:,2));
    allsigmaCloseEuly(k)=norm(xyref(:,2)-xy3z4(2,:)')/norm(xyref(:,2));
    allsigmaHeuny(k)=norm(xyref(:,2)-xy4z4(2,:)')/norm(xyref(:,2));
    allsigmaAMy(k)=norm(xyref(:,2)-xy5z4(2,:)')/norm(xyref(:,2));
end

loglog(hv, allsigmaOpenEuly, '-*r', 'DisplayName', 'Open Euler');
xlabel('h');
ylabel('\sigma y');
hold on;
loglog(hv, allsigmaCloseEuly, '-*g', 'DisplayName', 'Closed Euler');
loglog(hv, allsigmaHeuny, '-*b', 'DisplayName', 'Heun');
loglog(hv, allsigmaAMy, '-*y', 'DisplayName', 'Adams-Moulton');
legend(labels);
hold off;


%funkcje

%otwarta metoda Eulera
function dxydt=openeul(t2,xy2,p1,p2,p3,p4,h)

    for i=1:(length(t2)-1)
        xy2(:,i+1)=xy2(:,i) + h*LotVol(t2(i), xy2(:,i), p1, p2, p3, p4);
    end
    
    dxydt=xy2;
end

%zamknieta metoda Eulera
function dxydt=closeeul(t2,xy3,p1,p2,p3,p4,h)
    
    for i=1:(length(t2)-1)
        
        fun=@(xynext)[
            xynext - xy3(:,i) - h * LotVol(t2(i+1), xynext, p1,p2,p3,p4);
        ];
        xy3(:,i+1)=fsolve(fun,xy3(:,i),optimoptions('fsolve', 'Display', 'none'));
    
    end

    dxydt=xy3;
end

%otwarta metoda Heuna
function dxydt=Heun(t2,xy4,p1,p2,p3,p4,h)

    for i=1:(length(t2)-1)
        xy4(:,i+1)=xy4(:,i) + 0.5*h*(LotVol(t2(i), xy4(:,i), p1, p2, p3, p4) + LotVol(t2(i) + h, xy4(:,i) + h*LotVol(t2(i), xy4(:,i), p1, p2, p3, p4), p1, p2, p3, p4));
    end
    
    dxydt=xy4;
end

%zamknieta metoda Adamsa-Moultona
function dxydt=AdamsMoul(t2,xy5,p1,p2,p3,p4,h)

    B=[5/12, 8/12, (-1/12)];
    
    for i=1:(length(t2)-1)
        if i<3
            fun=@(xynext)[
            xynext - xy5(:,i) - h * LotVol(t2(i+1), xynext, p1,p2,p3,p4);
        ];
        xy5(:,i+1)=fsolve(fun,xy5(:,i),optimoptions('fsolve', 'Display', 'none'));
        else
            AM=@(xynext)[
                xynext - xy5(:,i) - h*B(1)*LotVol(t2(i+1), xynext, p1, p2, p3, p4) - h*B(2)*LotVol(t2(i), xy5(:,i), p1, p2, p3, p4) - h*B(3)*LotVol(t2(i-1), xy5(:,i-1), p1, p2, p3, p4);
                ];
            xy5(:,i+1)=fsolve(AM,xy5(:,i),optimoptions('fsolve', 'Display', 'none'));
        end
    end
    
    dxydt=xy5;
end

%funkcje
function dxydt = LotVol(t, xy, p1, p2, p3, p4)
    dxydt=zeros(2,1);
    dxydt(1) = p1*xy(1) - p2*xy(1)*xy(2);
    dxydt(2) = p3*xy(1)*xy(2) - p4*xy(2);
end