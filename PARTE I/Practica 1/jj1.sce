t=[1.00	0	0	0	0	0	0	0	0	0
1.00	1.00	0	0	0	0	0	0	0	0
1.00	1.00	1.00	0	0	0	0	0	0	0
1.00	1.00	1.00	1.00	0	0	0	0	0	0
1.00	1.00	1.00	1.00	0.67	0	0	0	0	0
1.20	1.20	1.00	1.00	1.00	0.86	0	0	0	0
1.64	1.50	1.50	1.64	1.64	1.64	1.38	0	0	0
2.21	2.47	2.36	2.41	2.47	2.41	2.36	2.26	0	0
2.82	3.06	3.10	3.10	3.10	3.10	3.09	3.06	3.02	0
2.68	3.66	3.80	3.81	3.76	3.77	3.79	3.76	3.77	3.79];

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

plot(x,t,"-o");
hl=legend(['normal';'2 hilos';'4 hilos';'8 hilos';'16 hilos';'32 hilos';'64 hilos';'128 hilos';'512 hilos';'1024 hilos';],"in_upper_left");
xtitle( 'Implementacion con Hilos', 'Tamaño', 'Tiempo(s)' ) ;

