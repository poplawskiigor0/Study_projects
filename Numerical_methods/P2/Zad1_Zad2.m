load MNUB_24L_P2_dane32.mat;

%deklaracje zmiennych, macierzy i komórek
X=cell(1,20); %komórki wyników X i Y
Y=cell(1,20);
Vav=zeros(1,20); %prędkośc średnia
Xerrabs=cell(1,20); %bezw. błędy wzgledne
Yerrabs=cell(1,20);
Verrabs=cell(1,20);
V=cell(1,20); %prędkośc
lengthall=0; %ilosc wszystkich pomiarów
xsum=0;
ysum=0;
figure;
xlabel("X [m]");
ylabel("Y [m]");
grid on;
hold on;
for i=1:20
    X{i}=zeros(1,length(t{i}));
    Y{i}=zeros(1,length(t{i}));
    V{i}=zeros(1,length(t{i})-1);
    for j=1:length(t{i})
        X{i}(j)=(D{i}(j,1)*D{i}(j,1)-D{i}(j,2)*D{i}(j,2)+16)/8;
        Y{i}(j)=sqrt(D{i}(j,1)*D{i}(j,1)-X{i}(j)*X{i}(j));
        if j>=2
            V{i}(j-1)=(sqrt((X{i}(j)-X{i}(j-1))^2+(Y{i}(j)-Y{i}(j-1))^2))/(t{i}(j)-t{i}(j-1)); %wyznaczanie prędkości
        end
    end
    Xerrabs{i}=abs(xref{i}'-X{i}); %oblicznie błędów względnych
    Yerrabs{i}=abs(yref{i}'-Y{i});
    Vav(i)=mean(V{i})*length(V{i});
    xsum=sum(Xerrabs{i})+xsum; %sumowanie wszystkich X oraz Y
    ysum=sum(Yerrabs{i})+ysum;
    lengthall=lengthall+length(V{i}); %sumowanie długości wszystkich wektorów
    plot(X{i},Y{i});
end
vav=sum(Vav)/lengthall; 
verr=abs(vav-vref);  %obliczanie średnich błędów bezwzględnych wyznaczania X i Y i prędkości
xerrall=xsum/(lengthall+20); 
yerrall=ysum/(lengthall+20);
hold off;

%Zad.2
M=15;
K=10;
tM=cell(1,20);
tscale=cell(1,20);
tperfM = cell(1,20);
Fi=cell(1,20);
y=cell(1,20);
p1=cell(1,20);
p2=cell(1,20);

for i=1:20
    tperfM{i} = linspace(0, t{i}(length(t{i})), M); %idealny rozklad wektora t na M punktów
    tM{i}=zeros(1,M);
    y{i}=zeros(M,2); %zmienna odpowiedzialna za przechowanie odległości od czujników w wybranych punktach czasu
    tscale{i}=zeros(1,length(t{i}));
    for j=1:M %funkcja do znajdywania najbliższych wartości idealnego rozkładu
        difftmax=0;
        for m=1:length(t{i})
            difft=abs(tperfM{i}(j)-t{i}(m));
            if m==1
                difftmax=difft;
                tM{i}(j)=t{i}(m);
                y{i}(j,1)=D{i}(m,1);
                y{i}(j,2)=D{i}(m,2);
            end
            if difft<difftmax
                difftmax=difft;
                tM{i}(j)=t{i}(m);
                y{i}(j,1)=D{i}(m,1);
                y{i}(j,2)=D{i}(m,2);
            end
        end
    end 
    tM{i}=tM{i}/tM{i}(M)*2-1; %przeskalowanie wektroów tak by wartości zawierały się od -1 do 1
    tscale{i}=t{i}/t{i}(length(t{i}))*2-1;
end

for i=1:20 %oblicznie matcierzy Fi
    Fi{i}=zeros(M,K);
    for j=1:M
        for k=0:K-1
            Fi{i}(j,k+1)=PolyLeg(tM{i}(j),k);
        end
    end 
    p1{i}=(Fi{i}'*Fi{i})\Fi{i}'*y{i}(:,1);
    p2{i}=(Fi{i}'*Fi{i})\Fi{i}'*y{i}(:,2);
end

est1=cell(1,20);
est2=cell(1,20);
X2=cell(1,20);
Y2=cell(1,20);
V2av=zeros(1,20);
X2errabs=cell(1,20);
Y2errabs=cell(1,20);
V2errabs=cell(1,20);
V2=cell(1,20);
lengthall2=0;
x2sum=0;
y2sum=0;
figure
hold on;
xlabel("X [m]");
ylabel("Y [m]");
grid on;
for i=1:20
    X2{i}=zeros(1,length(t{i}));
    Y2{i}=zeros(1,length(t{i}));
    V2{i}=zeros(1,length(t{i})-1);
    est1{i}=zeros(1,length(t{i}));
    est2{i}=zeros(1,length(t{i}));
    for j=1:length(t{i})
        for k=1:K
            est1{i}(j)=est1{i}(j)+p1{i}(k)*PolyLeg(tscale{i}(j),k-1);
            est2{i}(j)=est2{i}(j)+p2{i}(k)*PolyLeg(tscale{i}(j),k-1);
        end
        X2{i}(j)=(est1{i}(j)*est1{i}(j)-est2{i}(j)*est2{i}(j)+16)/8;
        Y2{i}(j)=sqrt(est1{i}(j)*est1{i}(j)-X2{i}(j)*X2{i}(j));
        if j>=2
            V2{i}(j-1)=(sqrt((X2{i}(j)-X2{i}(j-1))^2+(Y2{i}(j)-Y2{i}(j-1))^2))/(t{i}(j)-t{i}(j-1));
        end
    end
    X2errabs{i}=abs(xref{i}'-X2{i});
    Y2errabs{i}=abs(yref{i}'-Y2{i});
    V2av(i)=mean(V2{i})*length(V2{i});
    x2sum=sum(X2errabs{i})+x2sum;
    y2sum=sum(Y2errabs{i})+y2sum;
    lengthall2=lengthall2+length(V2{i});
    plot(X2{i},Y2{i});
end
v2av=sum(V2av)/lengthall2;
v2err=abs(v2av-vref);
x2errall=x2sum/(lengthall2+20);
y2errall=y2sum/(lengthall2+20);

function poly = PolyLeg(t,k) %funkcja odpowiadająca za wyznacznie wielomianów Legendre
    if k==0
      poly=1;  
    elseif k==1
      poly=t;  
    else
    poly=(2*k-1)/k*t*PolyLeg(t,k-1)-(k-1)/k*PolyLeg(t,k-2);
    end
end