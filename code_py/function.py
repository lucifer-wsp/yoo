print ("Test the function with pythod.\n");


def calc_sum (n):
    "This function is used to calc sum by given number."
    res_sum = 0;
    for number in range (n+1):
        res_sum += number;
    return res_sum;

print ("The func doc string is \'%s\'.\n" %(calc_sum.__doc__));
print ("The sum of %d is %d.\n" %(10,calc_sum(10)));
