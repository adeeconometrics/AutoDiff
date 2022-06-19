from sympy.abc import a,b 
from sympy import sin, cos, tan, cot, sec, csc
from sympy import sinh, cosh, tanh, coth, sech, csch

from sympy import asin, acos, atan, acot, asec, acsc
from sympy import asinh, acosh, atanh, acoth, asech, acsch

from sympy import diff, N

def test_trig(a_val:float, b_val:float) -> None:
    y = sin(a) * cos(a*b) * cot(a-b) *pow(a, b)/tan(a) * sec(b) - csc(b*a)
    dy_a = diff(y,a)
    dy_b = diff(y,b)

    print(f'dy wrt a: {N(dy_a.subs(a,a_val).subs(b, b_val))}')
    print(f'dy wrt b: {N(dy_b.subs(a,a_val).subs(b, b_val))}')


def test_trigh(a_val:float, b_val:float) -> None:
    y = sinh(a) * cosh(a*b) * coth(a-b) *pow(a, b)/tanh(a) * sech(b) - csch(b*a)
    dy_a = diff(y,a)
    dy_b = diff(y,b)

    print(f'dy wrt a: {N(dy_a.subs(a,a_val).subs(b, b_val))}')
    print(f'dy wrt b: {N(dy_b.subs(a,a_val).subs(b, b_val))}')

def test_atrig(a_val:float, b_val:float) -> None:
    y = asin(a) * acos(a*b) * acot(a-b) *pow(a, b)/atan(a) * asec(b) - acsc(b*a)
    dy_a = diff(y,a)
    dy_b = diff(y,b)

    print(f'dy wrt a: {N(dy_a.subs(a,a_val).subs(b, b_val))}')
    print(f'dy wrt b: {N(dy_b.subs(a,a_val).subs(b, b_val))}')


def test_atrigh(a_val:float, b_val:float) -> None:
    y = asinh(a) * acosh(a*b) * acoth(a-b) *pow(a, b)/atanh(a) * asech(b) - acsch(b*a)
    dy_a = diff(y,a)
    dy_b = diff(y,b)

    print(f'dy wrt a: {N(dy_a.subs(a,a_val).subs(b, b_val))}')
    print(f'dy wrt b: {N(dy_b.subs(a,a_val).subs(b, b_val))}')

if __name__ == '__main__':
    a_val = 1.1
    b_val = 0.5
    
    test_trig(a_val,b_val)
    print('\n')
    test_trigh(a_val,b_val)
    print('\n')
    test_atrig(a_val,b_val)
    print('\n')
    test_atrigh(a_val,b_val)
    


