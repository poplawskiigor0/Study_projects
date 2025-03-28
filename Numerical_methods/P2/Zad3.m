load MNUB_24L_P2_dane32.mat;

%Zad.3
KMXerr=zeros(20,19);
KMYerr=zeros(20,19);
KMVerr=zeros(20,19);
for M=5:20 %kod wzięty w dodatkowe pętle by zmieniać wartości M i K
    for K=1:M-1
        tM=cell(1,20);
        tscale=cell(1,20);
        tperfM = cell(1,20);
        Fi=cell(1,20);
        y=cell(1,20); 
        p1=cell(1,20);
        p2=cell(1,20);
        
        for i=1:20
            tperfM{i} = linspace(0, t{i}(length(t{i})), M);
            tM{i}=zeros(1,M);
            y{i}=zeros(M,2);
            tscale{i}=zeros(1,length(t{i}));
            for j=1:M
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
            tM{i}=tM{i}/tM{i}(M)*2-1;
            tscale{i}=t{i}/t{i}(length(t{i}))*2-1;
        end
        
        for i=1:20
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
        hold on;
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
                Y2{i}(j)=real(sqrt(est1{i}(j)*est1{i}(j)-X2{i}(j)*X2{i}(j)));
                if j>=2
                    V2{i}(j-1)=(sqrt((X2{i}(j)-X2{i}(j-1))^2+(Y2{i}(j)-Y2{i}(j-1))^2))/(t{i}(j)-t{i}(j-1));
                end
            end
            X2errabs{i}=abs(X2{i}-xref{i}');
            Y2errabs{i}=abs(Y2{i}-yref{i}');
            V2av(i)=mean(V2{i})*length(V2{i});
            x2sum=sum(X2errabs{i})+x2sum;
            y2sum=sum(Y2errabs{i})+y2sum;
            lengthall2=lengthall2+length(V2{i});
        end
        v2av=sum(V2av)/lengthall2;
        KMVerr(M,K)=abs(v2av-vref);
        KMXerr(M,K)=x2sum/(lengthall2+20);
        KMYerr(M,K)=y2sum/(lengthall2+20);
    end
end

    figure;
    xlabel("M");
    ylabel("K");
    zlabel("Średni błąd bezwzględny wyznaczania prędkości [m/s]");
    grid on;
    hold on;
    for M=5:20
        for K=1:M-1
            scatter3(M,K,KMVerr(M,K),'filled');
        end
    end
    hold off;

    figure;
    xlabel("M");
    ylabel("K");
    zlabel("Średni błąd bezwzględny wyznaczania współrzędnej X [m]");
    grid on;
    hold on;
    for M=5:20
        for K=1:M-1
            scatter3(M,K,KMXerr(M,K),'filled');
        end
    end
    hold off;

    figure;
    xlabel("M");
    ylabel("K");
    zlabel("Średni błąd bezwzględny wyznaczania współrzędnej Y [m]");
    grid on;
    hold on;
    for M=5:20
        for K=1:M-1
            scatter3(M,K,KMYerr(M,K),'filled');
        end
    end
    hold off;

    function poly = PolyLeg(t,k)
            if k==0
              poly=1;  
            elseif k==1
              poly=t;  
            else
            poly=(2*k-1)/k*t*PolyLeg(t,k-1)-(k-1)/k*PolyLeg(t,k-2);
            end
    end