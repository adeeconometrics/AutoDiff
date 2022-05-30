Possible sources of error
1. Operator precedence during operator overloading
2. Did not properly load values into memory (unordered map)
    1. Find alternative data structure to represent the tape
        -- unordered map is not the answer
        -- list seem to be a promising substitute
3. Implicit compiler optimization which overrule operator ordering 