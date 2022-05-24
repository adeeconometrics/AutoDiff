from collections import defaultdict

class Variable:
    def __init__(self, value, local_gradients=[]):
        self.value = value
        self.local_gradients = local_gradients

    def __add__(self, other):
        return add(self, other)

    def __mul__(self, other):
        return mul(self, other)

    def __sub__(self, other):
        return add(self, neg(other))

    def __truediv__(self, other):
        return mul(self, inv(other))


def add(a, b):
    value = a.value + b.value
    local_gradients = (
        (a, 1),
        (b, 1)
    )
    return Variable(value, local_gradients)


def mul(a, b):
    value = a.value * b.value
    local_gradients = (
        (a, b.value),
        (b, a.value)
    )
    return Variable(value, local_gradients)


def neg(a):
    value = -1 * a.value
    local_gradients = (
        (a, -1),
    )
    return Variable(value, local_gradients)


def inv(a):
    value = 1. / a.value
    local_gradients = (
        (a, -1 / a.value**2),
    )
    return Variable(value, local_gradients)

def get_gradients(variable):
    """ Compute the first derivatives of `variable` 
    with respect to child variables.
    """
    gradients = defaultdict(lambda: 0)
    
    def compute_gradients(variable, path_value):
        for child_variable, local_gradient in variable.local_gradients:
            # "Multiply the edges of a path":
            value_of_path_to_child = path_value * local_gradient
            # "Add together the different paths":
            print(gradients[child_variable])

            gradients[child_variable] += value_of_path_to_child
            # recurse through graph:
            compute_gradients(child_variable, value_of_path_to_child)
    
    compute_gradients(variable, path_value=1)
    # (path_value=1 is from `variable` differentiated w.r.t. itself)
    return gradients



if __name__ == '__main__':

    def f(a, b):
        return (a / b - a) * (b / a + a + b) * (a - b)

    a = Variable(230.3)
    b = Variable(33.2)
    y = f(a, b)

    gradients = get_gradients(y)

    print (f'value: {y.value}')
    # print("The partial derivative of y with respect to a =", gradients[a])
    # print("The partial derivative of y with respect to b =", gradients[b])
    for i in gradients.values():
        print(i)
