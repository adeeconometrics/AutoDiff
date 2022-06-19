from __future__  import annotations
from collections import defaultdict
from typing import Dict

"""
This method contains reverse-mode
"""

class Symbol: 
    def __init__(self, value:float, local_gradients:tuple = ()) -> None:
        self.value = value 
        self.local_gradients = local_gradients


    def __add__(self, other:Symbol) -> Symbol:
        return Symbol(
            value = self.value + other.value, 
            local_gradients = (
                (self, 1.0),
                (other, 1.0)
            )
        )

    def __sub__(self, other:Symbol) -> Symbol:
        return Symbol(
            value = self.value - other.value, 
            local_gradients = (
                (self, 1.0),
                (other, 1.0)
            )
        )

    def __mul__(self, other:Symbol) -> Symbol:
        return Symbol(
            value = self.value * other.value, 
            local_gradients = (
                (self, other.value),
                (other, self.value)
            )
        )

    def __neg__(self) -> Symbol:
        return Symbol(
            value = -1 * self.value,
            local_gradients=(
                (self, -1)
            )
        )

    def __truediv__(self, other:Symbol) -> Symbol:
        return self * Symbol.inv(other)

    @staticmethod
    def inv(other) -> Symbol:
        return Symbol(
            value = 1.0 / other.value,
            local_gradients = (
                (other, -1/(pow(other.value, 2)))
            )
        )

def gradients(variable:Symbol) -> Dict[Symbol, float]: 
    _gradients:dict = defaultdict(lambda: 0.0)

    def _compute_gradients(variable:Symbol, path_value:float) -> None:
        print(type(variable.local_gradients))

        # for child, local_gradient in variable.local_gradients:
        #     value_of_path_to_child = path_value * local_gradient
        #     _gradients[child] += value_of_path_to_child
        #     _compute_gradients(child, value_of_path_to_child)

    _compute_gradients(variable, path_value = 1)

    return _gradients

if __name__ == '__main__':
    
    def f(a: Symbol, b: Symbol) -> Symbol:
        return (a / b - a) * (b / a + a + b) * (a - b)

    a = Symbol(230.3)
    b = Symbol(33.2)
    y = f(a, b)

    df = gradients(y)

    print(f"d value: {y.value}")
    print(f"df/da: {df[a]}", f"df/db: {df[b]}", sep='\n')

