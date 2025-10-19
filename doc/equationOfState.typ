= Residual Properties from Cubic EOS

== PengRobinson Equation

$
p = (R T)/(tilde(V)-b) - a/(tilde(V)(tilde(V)+b)+b(tilde(V)-b)) \
a = a_c alpha \
a_c = 0.457235 (R T_c)^2/p_c \
sqrt(alpha) = 1+kappa (1-sqrt(T_r))\
kappa=0.37464+1.54226 omega - 0.26992 omega^2 \
b = 0.077796 (R T_c)/p_c
$

Volume shifting
$
  V = tilde(V) - c \
  tilde(V) = V + c \
  c = 0.50033 (R T_c)/p_c (0.25969 - z_(R A))
$

=== polynomial form
$
tilde(V)^3 + (b-(R T)/p)tilde(V)^2 + (a/p - 2 (b R T)/p -3 b^2) tilde(V) + (b^3 - (a b)/p + (b^2 R T)/p) =0
$

// Dimensionless
// $
// z^3 + (B-1)z^2 + (A-2B-3B^2)z + (B^3+B^2-A B)=0 \
// z = (p a_j)/(R T) \
// A = (p a)/(R T)^2\
// B = (p b)/(R T)
// $

=== Residual Energy

Internal energy
$
U^R/(R T) & = 1/(R T) integral_infinity^V [T((partial p)/(partial T))_V - p] dif V \
          & = (a - T (dif a)/(dif T))/(R T) integral_infinity^V (dif V)/(V(V+b)+b(V-b)) \
          & = (a - T (dif a)/(dif T))/(R T) integral_infinity^(tilde(V)-c) (dif tilde(V))/(tilde(V)(tilde(V)+b)+b(tilde(V)-b)) \
          & = (a - A (dif a)/(dif T))/(2 sqrt(2) b R T) ln (tilde(V) - c + (1-sqrt(2))b)/(tilde(V) -c +(1+sqrt(2))b)\
          & = (a - A (dif a)/(dif T))/(2 sqrt(2) b R T) ln (V + (1-sqrt(2))b)/(V +(1+sqrt(2))b)
$

Volume shifting doesn't change the form of residual properties, nor does it affect partial derivatives.

Enthalpy
$
H^R/(R T) = Z - 1 + U^R/(R T)
$

=== Residual Heat capacity
Fixed volume:
$
C_v^R/R & = T/R integral_infinity^V ((partial^2 p)/(partial T^2))_V dif V \
        & = - (dif^2 a)/(dif T^2) dot T/R integral_infinity^V (dif V)/(V(V+b)+b(V-b)) \
        & = - (dif^2 a)/(dif T^2) dot (p)/(2sqrt(2) R^2 B) ln((Z-(sqrt(2)-1)B)/(Z+(sqrt(2)+1)B))
$
Fixed pressre:
$
(C_p^R-C_v^R)/R & = -1 -T/R ((partial p)/(partial T))_V^2/((partial p)/(partial V))_T \
                & = -1 -T/R (R/(V-b)-(dif a)/(dif T) 1/(V(V+b)+b(V-b)))^2/((a(V+b))/[V(V+b)+b(V-b)]^2 - (R T)/(V-b)^2 )
$




== Mixing rule
$
a = sum_i sum_j x_i x_j sqrt(a_i a_j)(1-k_(i j)) \
b = sum_i x_i b_i \
c = sum_i x_i c_i
$

=== Computation of $dif a\/dif T$
Single component:
$
(dif a)/(dif T) = a_c (dif alpha)/(dif T)=-a_c kappa sqrt(alpha/(T T_c)) \


(dif^2 a)/(dif T^2)=a_c (dif^2 alpha)/(dif T^2)=a_c (kappa (alpha-T (dif a)/(dif T)))/(2 T sqrt(T T_c alpha))
$

Mixture:
$
(dif a)/(dif T) = sum_i sum_j x_i x_j (1-k_(i j)) dif/(dif T) sqrt(a_i a_j)\


dif/(dif T) sqrt(a_i a_j) = 1/(2 sqrt(a_i a_j)) (a_i (dif a_j)/(dif T) + a_j (dif a_i)/(dif T)) \

(dif^2 a)/(dif T^2) = sum_i sum_j x_i x_j (1-k_(i j)) dif^2/(dif T^2)sqrt(a_i a_j) \

dif^2/(dif T^2)sqrt(a_i a_j) = 
1/(4 (a_i a_j)^1.5) 
[
    2 a_i^2 a_j (dif^2 a_j)/(dif T^2) - a_i^2 ((dif a_j)/(dif T))^2 + 2a_i (dif a_i)/(dif T) a_j (dif a_j)/(dif T) + a_j^2 (2a_i (dif^2 a_i)/(dif T^2) - ((dif a_i)/(dif T))^2)
]
// 1/(4 a_i a_j)[2sqrt(a_i a_j)(a_i (dif^2 a_j)/(dif T^2) + 2(dif a_i)/(dif T) (dif a_j)/(dif T) +a_j (dif^2 a_i)/(dif T^2) ) - (a_i (dif a_j)/(dif T) + a_j (dif a_i)/(dif T))(dif)/(dif T)sqrt(a_i a_j) ]
$
