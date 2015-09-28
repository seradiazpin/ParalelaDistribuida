t=[0.004	0
0.004	0.005
0.004	0.005
0.005	0.005
0.005	0.005
0.006	0.006
0.012	0.012
0.049	0.046
0.377	0.354
10.131	7.550];

r=[0.004
0.004
0.004
0.004
0.004
0.006
0.018
0.106
1.042
26.654
];

x=[2
4
8
16
32
64
128
256
512
1024
];
plot(x,t,"-o",x,r,"-*");
hl=legend(['2 procesos';'4 procesos';'normal'],"in_upper_left");
title('Implementacion con Procesos','fontsize',6);
xlabel("Tamaño", "fontsize", 5);
ylabel("Tiempo(s)", "fontsize", 5);






