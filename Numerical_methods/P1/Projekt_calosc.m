load ('MNUB_24L_P1_dane32.mat');
N=165; %zapamietuje liczbe punktów w czasie by nie pisać ciągle 165
A=zeros(3,3); 
for i=1:3
    A(i,:)=[2*(R(i,1)-R(4,1)), 2*(R(i,2)-R(4,2)), 2*(R(i,3)-R(4,3))]; %obliczam A po kolei wierszami na podstawie przekształconego równania
end

disp(A);
%rozkład macierzy A na L i U
U=A;
L=eye(3,3);
for i=2:3
    for j=1:i-1
        L(i,j)=A(i,j)/A(j,j);
        U(i,:)=U(i,:)-U(j,:)*L(i,j);
    end
end

%disp(A);
%disp(L);
%disp(U);

B=zeros(N,3);
X=zeros(N,3); %macierz rozwiązań współrzędnych

for n=1:N
    %obliczam wektor b dla każdej chwili czasu na podstawie
    %przekształconego równania i wpisuje w macierz B
    for i=1:3
        B(n,i)=D(n,4)*D(n,4)-D(n,i)*D(n,i)+(R(i,1))^2+(R(i,2))^2+(R(i,3))^2-(R(4,1))^2-(R(4,2))^2-(R(4,3))^2;
    end

    y=L\(B(n,:))';
    X(n,:)=U\y; %na podstawie wektora b oraz macierzy L i U obliczam wektor x dla każdej chwili i wpisuje w wiersz macierzy X
end

%wykres wartości współrzędnych środka ciężkości osoby w trakcie ruchu.
plot(t,X(:,1),'r-.');
hold on
xlabel('Czas[s]');
ylabel('x,y,z[m]');
plot(t,X(:,2),'b-.');
plot(t,X(:,3),'g-.');
legend('x','y','z');
hold off

%wykres trówymiarowej trajektorii ruchu osoby
figure;
scatter3(X(:,1), X(:,2), X(:,3), 'r','.');
zlim([0,3]);
xlabel('x[m]');
ylabel('y[m]');
zlabel('z[m]');
grid on;


%disp(L*U);
%disp(B);
%disp(X);

%Zaburznie - zad 3

MaxErrX=zeros(19,1); %wektor błedów max X
MaxErrB=zeros(19,1); %wektor błedów max B
sigmaV=zeros(19,1); %wektor poziomów zaburzenia
Est=zeros(19,1); %wektor oszacowania błędów

%pętla dla 19 róznych odchyleń sigma
for k=1:19
    Dz=D;
    if k<=10
        sigma=10^(-3)*k;
    else
        sigma=10^(-2)*(k-9);
    end

    Z=randn(N,4)*sigma; %generacja losowych zaburzeń o rozkładzie normalnym
    sigmaV(k)=sigma;

    Dz=Dz.*(Z+1); %zaburzenie D
    Bz=zeros(N,3); %zaburzone B
    Xz=zeros(N,3); %zaburzone X
    ErrNormX=zeros(N,1);
    ErrNormB=zeros(N,1);

    for n=1:N
        %oblicznie zaburzonego B
        for i=1:3
        Bz(n,i)=Dz(n,4)*Dz(n,4)-Dz(n,i)*Dz(n,i)+(R(i,1))^2+(R(i,2))^2+(R(i,3))^2-(R(4,1))^2-(R(4,2))^2-(R(4,3))^2;
        end

    yz=L\(Bz(n,:))';
    Xz(n,:)=U\yz;

    %zagregowane błędy względne
    ErrNormX(n)=norm(Xz(n,:)-X(n,:))/norm(X(n,:));
    ErrNormB(n)=norm(Bz(n,:)-B(n,:))/norm(B(n,:));
    end

    %maksymalne zagregowane błędy względne
    MaxErrX(k)=max(ErrNormX);
    MaxErrB(k)=max(ErrNormB);
    %obliczanie oszacowanych błędów
    Est(k)=cond(A)*MaxErrB(k);
end

%wykres zależności wartości maksymalnego zagregowanego błędu względnego rozwiązania oraz oszacowania tego błędu od poziomu zaburzenia
figure;
semilogx(sigmaV,MaxErrX);
hold on
semilogx(sigmaV,Est);
xlabel('poziom zaburzenia sigma d');
ylabel('maksymalny zagregowany błąd względny');
legend('maksymalny błąd', 'estymata')
hold off

%Zad 4

CondAz=zeros(150,4); %macierz liczb kondycyjnych dla różnych zaburzeń A
DetAz=zeros(150,4); %macierz wyznaczników dla różnych zaburzeń A
sigmaz=linspace(-0.1,0.1,150); %wartości odchyleń
MaxErrX4=zeros(150,4);
for l=1:4
    for k=1:150
    
        Rz=R;
        Rz(l,3)=Rz(l,3)*(sigmaz(k)+1); %zaburzenie składowej z w macierzy R dla każdego czujnika osobno
        Xz4=zeros(N,3);
        Bz4=zeros(N,3);
        ErrNormX4=zeros(N,1);
    
        Az=zeros(3,3);
            for i=1:3
                Az(i,:)=[2*(Rz(i,1)-Rz(4,1)), 2*(Rz(i,2)-Rz(4,2)), 2*(Rz(i,3)-Rz(4,3))];
            end
            
            CondAz(k,l)=cond(Az); %wpisywanie liczby kondycyjnej dla każdej zaburzonej macierzy A
            DetAz(k,l)=det(Az); %wpisywanie wartości wyznacznika każdej zaburzonej macierzy A

            %rozkład zaburzonego Az na L i U
            Uz=Az;
            Lz=eye(3,3);
            
            for i=2:3
                for j=1:i-1
                    Lz(i,j)=Az(i,j)/Az(j,j);
                    Uz(i,:)=Uz(i,:)-Uz(j,:)*Lz(i,j);
                end
            end
    
            %obliczanie wektora wyników
        for n=1:N
            for i=1:3
            Bz4(n,i)=D(n,4)*D(n,4)-D(n,i)*D(n,i)+(Rz(i,1))^2+(Rz(i,2))^2+(Rz(i,3))^2-(Rz(4,1))^2-(Rz(4,2))^2-(Rz(4,3))^2;
            end
    
            yz4=Lz\(Bz4(n,:))';
            Xz4(n,:)=Uz\yz4;
        
            %zagregowany błąd względny
            ErrNormX4(n)=norm(Xz4(n,:)-X(n,:))/norm(X(n,:));
        end
    
        %maksymalny zagregowany błąd względny
        MaxErrX4(k,l)=max(ErrNormX4);
    end
end

%wykres zależności liczby kondycyjnej macierzy A od poziomu zaburzenia
figure;
plot(sigmaz,CondAz(:,1));
hold on
plot(sigmaz,CondAz(:,2));
plot(sigmaz,CondAz(:,3));
plot(sigmaz,CondAz(:,4));
xlabel('poziom zaburzenia sigma z');
ylabel('wartość liczby kondycyjnej macierzy A');
legend('czujnik 1', 'czujnik 2', 'czujnik 3', 'czujnik 4');
hold off

%wykres zależności wartości wyznacznika macierzy A od poziomu zaburzenia
figure;
plot(sigmaz,DetAz(:,1));
hold on
plot(sigmaz,DetAz(:,2));
plot(sigmaz,DetAz(:,3));
plot(sigmaz,DetAz(:,4));
xlabel('poziom zaburzenia sigma z');
ylabel('wartość wyznacznika macierzy A');
legend('czujnik 1', 'czujnik 2', 'czujnik 3', 'czujnik 4');
hold off

%wykres zależności wartości maksymalnego zagregowanego błędu względnego rozwiązania od poziomu zaburzenia
figure;
plot(sigmaz,MaxErrX4(:,1));
hold on
plot(sigmaz,MaxErrX4(:,2));
plot(sigmaz,MaxErrX4(:,3));
plot(sigmaz,MaxErrX4(:,4));
xlabel('poziom zaburzenia sigma z');
ylabel('maksymalny zagregowany błąd względny rozwiązania');
legend('czujnik 1', 'czujnik 2', 'czujnik 3', 'czujnik 4');
