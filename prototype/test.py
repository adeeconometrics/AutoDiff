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
        print(f'outer: {path_value}')

        for child_variable, local_gradient in variable.local_gradients:
            value_of_path_to_child = path_value * local_gradient

            print(f'\t local_gradient {local_gradient}', 
                    f'\t path value: {path_value}', 
                    f'\t inside before {gradients[child_variable]}',
                    sep = '\n')

            gradients[child_variable] += value_of_path_to_child
            print(f'\t inside after {gradients[child_variable]}')

            compute_gradients(child_variable, value_of_path_to_child)
    
    compute_gradients(variable, path_value=1)
    return gradients



if __name__ == '__main__':


    # a = Variable(4.0)
    # b = Variable(3.0)
    # c = a + b
    # d = a * c / a
    # df = get_gradients(d)
    # print(f'd value: {d.value}')
    # print(f'df/da : {df[a]}')
    # print(f'df/db : {df[b]}')

    def f(a, b):
        return (a / b - a) * (b / a + a + b) * (a - b)

    a = Variable(230.3)
    b = Variable(33.2)
    y = (a / b - a) * (b / a + a + b) * (a - b)

    gradients = get_gradients(y)

    print (f'd value: {y.value}')
    print("df/da =", gradients[a])
    print("df/db =", gradients[b])

    # for i in gradients.values():
    #     print(f'{id(i)}\t{i}')
