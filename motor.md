反电动势 $e_a$、$e_b$、$e_c$, 相电流 $i_a$、$i_b$、$i_c$

电磁功率 $P_e$, 转子机械角速度 $Ω$, 电角速度 $\omega_e$, 极对数 $p$, 电磁转矩 $T_e$, 负载转矩 $T_L$

转动惯量 $J$, 机械角速度差 $dΩ$, 时间差 $dt$, 摩擦系数/阻尼系数 $B_v$



电磁转矩方程：$$P_e = e_a i_a + e_b i_b + e_c i_c  = T_e Ω$$

机械角度与电角度关系：$$ Ω =  ω_e *  p$$

动力学方程：$$  T_e - T_L - B_v Ω = J \frac{dΩ}{dt}$$



Clark 变换后的 $\alpha-\beta$ 坐标系下的电磁转矩

$$T_e = \frac{3}{2} p (\frac{e_α}{ω_e} i_\alpha + \frac{e_\beta}{ω_e} i_\beta)$$



转子磁链基基波分量的赋值 $\phi_{fm'}$

$i_d = 0 $ 时 ，$T_e = \frac{3}{2} \phi_{fm'} i_q$







$$
\begin{bmatrix}
I_\alpha  \\ I_\beta
\end{bmatrix}
= \frac{2}{3}
\begin{bmatrix}
1 & -\frac{1}{2} & -\frac{1}{2}  \\
0 & \frac{\sqrt{3}}{2} & -\frac{\sqrt{3}}{2} \\
\end{bmatrix}
\begin{bmatrix}
I_a  \\ I_b  \\ I_c
\end{bmatrix}
$$

$$
\begin{bmatrix}
I_d  \\ I_q
\end{bmatrix}
=
\begin{bmatrix}
cos(\theta) & sin(\theta)  \\
-sin(\theta) & cos(\theta) 
\end{bmatrix}
\begin{bmatrix}
I_\alpha  \\ I_\beta
\end{bmatrix}
$$


