= MartinHou81

$
  p=sum_(i=1)^5 (f_i (T))/(V-b)^i \
  f_i (T) = A_i + B_i T + C_i exp(-kappa T/T_c)
$

Special Temperature coefficient:
#table(
  columns: 6,
  align: (center),
  [],[1],[2],[3],[4],[5],
  [$A$],[0],[$A_2$],[$A_3$],[$A_4$],[0],
  [$B$],[$R$],[$B_2$],[$B_3$],[$B_4$],[$B_5$],
  [$C$],[$0$],[$C_2$],[$C_3$],[0],[0],
)

Known parameter(s):
$
  kappa=5.475 \
  b=V_c - (beta V_c)/(15 Z_c)\
  beta = 20.533Z_c -31.883Z_c^2
$
Unknown parameters: 9 temperature params.

== Critical Point
$
Z_c &= (p_c V_c)/(R T_c ) \
m &= ((partial p)/(partial T))_V_c \
((partial p)/(partial V))_T_c &= 0 \
((partial^2 p)/(partial V^2))_T_c &= 0 \
((partial^3 p)/(partial V^3))_T_c &<= 0 \
((partial^4 p)/(partial V^4))_T_c &= 0
$

Leads to:
$
p_c &= sum_(i=1)^5 (f_i (T_c))/(V_c-b)^i \

5 p_c &= sum_(i=1)^4 (5-i) (f_i (T_c))/(V_c-b)^i \
20 p_c &= sum_(i=1)^3 (5-i)(4-i) (f_i (T_c))/(V_c-b)^i \
9 p_c &= 19/5 (f_1(T_c))/(V_c-b) + (f_2(T_c))/(V_c-b)^2
$

Slope at critical point:
$
  ((partial p)/(partial T))_V = sum_(i=1)^5 (B_i - C_i kappa e^(-kappa T_r)\/T_c )/(V-b)^i \
  m=((partial p)/(partial T))_(V_c) = sum_(i=1)^5 (B_i - C_i kappa e^(-kappa))/(V_c - b)^i 
$

// Pushing Clausius-clapeyron relation to critical point:
// $
//   m=lim_(T->T_c^-) (dif p^s)/(dif T) = lim_(V_g->V_L^+) (Delta_v H)/(T (V_g - V_L)) \
//   Delta_v H = p(V_g - V_L) + sum_(i=2)^5 (A_i +(1+kappa T_r)C_i e^(-kappa T_r))/(i-1) (1/(V_g-b)^(i-1)-1/(V_L-b)^(i-1)) \
//   m= p_c/T_c + lim_(V_g->V_L^+) sum_(i=2)^5 (A_i + (1+kappa)C_i e^(-kappa))/((i-1) (V_g - V_L)) (1/(V_g-b)^(i-1)-1/(V_L-b)^(i-1))
// $
// When $i>=3$, the limit is 0. So we have
// $
//   m=p_c / T_c  + (A_2 + C_2(1+kappa)e^(-kappa))/(V_c-b)^2
// $

Critical point provides 5 equations. Now we have 5 equations against 9 unknown parameters.

== Bolye Temperature $T_B$
$
  lim_(p->0) ((partial (p V))/(partial p))_T_B = 0
$
This derivative can be expressed as 
$
  ((partial (p V))/(partial p))_T &= V + p ((partial V)/(partial p))_T \
   &= V + p \/ ((partial p)/(partial V))_T \
   &= V + (sum_(i=1)^5 (f_i (T))/(V-b)^i) / (
    sum_(i=1)^5 -i(f_i (T))/(V-b)^(i+1)   ) \
   &= (
    sum_(i=1)^5 f_i (i V-(V-b)) \/ (V-b)^(i+1)
   )/(
    sum_(i=1)^5 i f_i \/ (V-b)^(i+1)
   )
$

Applying limitation:
$
  lim_(p->0) ((partial (p V))/(partial p))_T_B 
    = lim_(V->+infinity) ((partial (p V))/(partial p))_T_B 
    = lim_(V->+infinity) (
    sum_(i=1)^5 f_i (i V-(V-b)) \/ (V-b)^(i+1)
   )/(
    sum_(i=1)^5 i f_i \/ (V-b)^(i+1)
   ) =0 
$
Only highest order takes effect in limitation:
$
   lim_(V->+infinity) (f_1 (T_B) (V - (V-b))/(V-b)^2 + f_2 (T_B) (2V-(V-b))/(V-b)^3)/(f_1 (T_B) \/ (V-b)^2) = 0 \
   lim_(V->+infinity) (b f_1(T_B) + (V+b)/(V-b) f_2(T_B))/ (f_1(T_B)) = 0 \
   f_2(T_B)=-b f_1(T_B) = -b R T_B
$

Bolye temperature provides 1 equation. Now we have 6 against 9.

== Gas-Liquid Equilibrium Point
Consider a gas-liquid equilibrium point $j$, with given temperature, pressure and molar volume of both phases:
$
  T_j, p_j, V_(g,j), V_(L,j) 
$

Obviously we have 2 equations:
$
  p_j = sum_(i=1)^5 (f_i (T_j))/(V_(g,j)-b)^i = sum_(i=1)^5 (f_i (T_j))/(V_(L,j)-b)^i
$

Now we have 8 against 9. In MH55 verion, $B_4=0$ so it can be solved now.

=== Integral from liquid to gas
$
  integral_(V_(L,j))^(V_(g,j)) p_j dif V = p_j (V_(g,j)-V_(L,j))
$

$
  p_j (V_(g,j)-V_(L,j)) 
  &= sum_(i=1)^5 integral_(V_(L,j))^(V_(g,j)) (dif V)/(V-b)^i   \
  &= f_1(T_j) ln V_(g,j)/V_(L,j) + sum_(i=2)^5 (f_i (T_j))/(1-i) [1/(V_(g,j)-b)^(i-1) - 1/(V_(L,j)-b)^(i-1)]
 $

Now we have 9 against 9. All parameters can be determined.



// This paragraph is commented because it leads to same equation as above. Actually useless
// == Equilibrium condition:
// Both phase should have same free energy:
// $
//   G_(L,j) = G_(g,j) \
//   Delta_v H_j = T_j Delta_v S_j \
//   H^R_(g,j)-H^R_(L,j) = T_j (S^R_(g,j)-S^R_(L,j))
// $

== Solve coefficients
Equations above can be transformed into a linear system:
$
  bold(A X)=bold(B)
$
where
$
  X=mat(A_2, B_2, C_2, A_3, B_3, C_3, A_4, B_4, B_5)^T
$

There is no non-linear term that multiplies temperature coefficients. However the matrix is heavily singular and process terrible condition number ($~10^(22)$). Some method must be employed.

1. Dimensionless processing \
  Each row is divided by a factor from critical point. If constant term is a pressure, divide by $P_c$; if $p*V$, divide by $p_c V_c$.
2. Primitive row operation \
  Row operation became available because of dimensionless. 
  For critical point constraints:
  ```cpp
    A.row(1) -= A.row(2);
    A.row(0) -= A.row(3);
  ```
3. Column scaling \
  Each temperature factor is scaled to be dimensionless.
  $
    tilde(A_i)=A_i/(p_c V_c^i) \
    tilde(B_i)=(B_i T_c)/(p_c V_c^i) \
    tilde(C_i)=C_i/(p_c V_c^i) e^(-k)
  $
  The scaling matrix 
  $
    bold(D)="diag"mat(1/(p_c V_c^2),T_c/(p_c V_c^2),exp(-k)/(p_c V_c^2),//2
    1/(p_c V_c^3),T_c/(p_c V_c^3),exp(-k)/(p_c V_c^3),//3
    1/(p_c V_c^4),T_c/(p_c V_c^4),//4
    T_c/(p_c V_c^5))^T \
    tilde(bold(X))=bold(D X) \
    bold(X) = bold(D^(-1) tilde(X)) \
    bold(A X)=bold(B) => bold(A D^(-1) tilde(X))=bold(B)
  $
  By normalization, each element in $bold(A D^(-1))$ have same dimension and similiar magnitude.
4. Adaptive row scaling \
  Divide each row by its maximum absolute value.

Above approaches will reduce condition number from $10^22$ to ~300. It can be easily solved by `fullPivLU`, and we get $tilde(bold(X))$ and then $bold(X)$.

== Residual Properties
Expression of residual enthalpy and entropy can be concluded:
$
  H^R &= p V - R T + integral_infinity^V [T ((partial p)/(partial T))_V - p] dif V \
  &= p V - R T + sum_(i=2)^5 (A_i + (1+kappa T_r)C_i e^(-kappa T_r))/((i-1)(V-b)^(i-1)) \

  S^R &= integral_infinity^V ((partial p)/(partial T))_V - R/V dif V \
  &=  lr(R ln (V-b)/(V) |)_infinity^V + sum_(i=2)^5 lr((B_i - C_i kappa \/T_c e^(-kappa T_r))/((1-i) (V-b)^(i-1)) |)_infinity^V \
  &= R ln(V-b)/V + sum_(i=2)^5 (B_i - C_i kappa\/T_c e^(-kappa T_r))/((1-i) (V-b)^i)
$
