= Redlich-Kwong Equation
$
  p=(R T)/(V-b) - a/(sqrt(T) V(V+b))
$

== Common Derivatives
$ ((partial p)/(partial T))_V &=  R/(V-b) + a/(2T sqrt(T) V(V+b))\
  ((partial^2p)/(partial T^2))_V &= - (3 a)/(4T^(5\/2) V(V+b))\
$

== Derivatie of residual heat capacity
Fixed volume:
$
  ((partial C_v^R)/(partial T))_p 
  &= (partial /(partial T))_p [T integral_infinity^V ((partial^2p)/(partial T^2))_V dif V] \
  &=  integral_infinity^V ((partial^2p)/(partial T^2))_V dif V + T ((partial V)/(partial T))_p ((partial^2p)/(partial T^2))_V \
  &= (3a)/(4b T^(5\/2)) ln(1+b/V) + T ((partial V)/(partial T))_p ((partial^2p)/(partial T^2))_V \
$