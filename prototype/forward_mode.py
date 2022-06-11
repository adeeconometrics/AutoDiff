from __future__ import annotations 
from typing import Tuple, Optional
import math as m

sec = lambda x: 1/cos(x)

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

    def __pow__(self, other:float) -> Symbol:
        df = Symbol(self.val**other.val,
                other*self.val**(other - 1)*self.dot)
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

if __name__ == '__main__':
    x = Symbol(1.5,1)
    y = Symbol(0.5,0)
    f = (x/y - cos(y)) * (x/y - cos(y) + sin(x/y))
    print(f.dot)
