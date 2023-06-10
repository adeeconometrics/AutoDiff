from __future__ import annotations 

from typing import Tuple, Optional, List, Callable
import math as m


sec = lambda x: 1/m.cos(x)

class Symbol:
    def __init__(self, value:float, dot:Optional[float] = None) -> None:
        self.val, self.dot = value, dot

    def __add__(self, other:Symbol) -> Symbol:
        df = Symbol(self.val + other.val,
                self.dot + other.dot)
        return df


    def __add__(self, other:Symbol) -> Symbol:
        df = Symbol(self.val + other.val,
                self.dot + other.dot)
        return df

    def __sub__(self, other:Symbol) -> Symbol:
        df = Symbol(self.val - other.val,
                self.dot - other.dot)
        return df

    def __mul__(self, other:Symbol) -> Symbol:
        df = Symbol(self.val * other.val,
                self.val*other.dot + other.val*self.dot)
        return df

    def __truediv__(self, other:Symbol) -> Symbol:
        df = Symbol(self.val / other.val,
                (self.dot*other.val - self.val*other.dot)/ pow(other.val, 2))
        return df

    def __pow__(self, other:Symbol) -> Symbol:
        df = Symbol(self.val**other.val,
                m.log(self.val)*pow(self.val, other.val)*other.dot)
        return df

def sin(x:Symbol) -> Symbol:
    df = Symbol(m.sin(x.val), m.cos(x.val)*x.dot)
    return df

def cos(x:Symbol) -> Symbol:
    df = Symbol(m.cos(x.val), -m.sin(x.val)*x.dot)
    return df

def tan(x:Symbol) -> Symbol:
    df = Symbol(m.tan(x.val), pow(sec(x.val), 2))
    return df

def make_jvp(fn:List[Callable], 
        args:List[Symbol]) -> List[float]: 
    return [f(*args).dot for f in fn]

if __name__ == '__main__':
    x = Symbol(1.5,0)
    y = Symbol(0.5,1)
    # todo: higher-order diff
    # f = lambda x,y: (x/y - cos(y)) * (x/y - cos(y) + sin(x/y))
    # f1 = f(x,y)
    # f2 = f1/x

    f = [lambda x,y: x*y + sin(x),
         lambda x,y: x+y+sin(x*y)]
    # jvp = make_jvp(f, [x,y])

    print(f[1](x,y).val, f[1](x,y).dot)
