print ("Excise 4.9:\n");
#1.using if...: statement and testing some number if is true or false from 0 to 4.
if 0 == True:
    print ("The number %d is True.\n" %(0));
else:
    print ("The number %d is False.\n" %(0));

if 1 == True:
    print ("The number %d is True.\n" %(1));
else:
    print ("The number %d is False.\n" %(1));

if 2 == True:
    print ("The number %d is True.\n" %(2));
else:
    print ("The number %d is False.\n" %(2));

if 3 == True:
    print ("The number %d is True.\n" %(3));
else:
    print ("The number %d is False.\n" %(3));

if 4 == True:
    print ("The number %d is True.\n" %(4));
else:
    print ("The number %d is False.\n" %(4));

#2.using the if...: statement to test 0 or 9 if it is between 0 and 9.
number = 0;
if number >= 0 and number <= 9:
    print ("The number %d is between 0 and 9.\n" %(number));
else:
    print ("The number %d isn't between 0 and 9.\n" %(number));

#3.using the if...:,elif...: and else: statement to test the sequence value.
sequence_tuple = (1,2,3,4,5);
value = 2;
if sequence_tuple[0] == value:
    print ("The first value is %d.\n" %(value));
elif sequence_tuple[1] == value:
    print ("The second value is %d.\n" %(value));
else:
    print ("The sequence don\'t have the value %d in first two elements.\n" %(value));

#4.create new map called fridge and add some food and visit all elements,then redo excise 3.
fridge = {};
fridge["肉"] = "鸡肉味儿的，嘎嘣脆。";
fridge["菜"] = "你个菜鸡，切..";
fridge["面包"] = "好像一坨翔呀，额..";
food_sought = fridge.keys();
for food in food_sought:
    print ("The food \'%s\' info :%s.\n" %(str(food),str(fridge.get(str(food)))));

for val in sequence_tuple:
    if val == value :
        print ("The %d value is contained .\n" %(value));
        break;
else:
    print ("The value %d isn't contained .\n" %(value));

#5.using while statement replace the for statement redo the excise 3.
fridge_list = [];
index = 0;
food_sought = tuple(food_sought);
while index < len(food_sought):
    fridge_list.append(food_sought[index]);
    index +=1;

while len(fridge_list)>0:
    print ("The current key is %s.\n" %(fridge_list[0]));
    fridge_list.pop(0);
else:
    print ("visit over...\n");

#6.using the try: statement to replace for...in...: to redo excise 3.
vis_val = "水果";
try:
    print ("The food \'%s\' info :%s.\n" %(vis_val,fridge[vis_val]));
except KeyError as error:
    print ("The food \'%s\' is not exists.\n" %(vis_val));


