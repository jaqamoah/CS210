import re
import string
import fileinput


contents = dict() # Dictionary to store items from the input file. 

# Method to display the frequency of a specific item
def display_specific_items(value):
    read_data() # Method to read the items from the input file and store them in a dictionary.
    key = contents.get(value)
    if(key) != None : # Checking if the item exists or not
       return contents[value]; # Return the frequency of the item selected
    else :
       return -1; # Return -1 if the item does not exist
    

# Method to read the items from the input file and store them in a dictionary.
def read_data(): 
    with open("CS210_Project_Three_Input_File.txt") as f: 
        for line in f :
          line = line.strip()
          if line in contents:
             contents[line]+=1
          else :
             contents[line]=1

# Method to write the items to a frequency.dat file.
def write_data(): 
    read_data()
    out = open("frequency.dat", "w")
    for key in contents.keys() :
        items = key +" "+ str(contents[key])+"\n"
        out.write(items)
    out.close()
 
# Method to display all of the items from the input file with their frequency.   
def display_all_items():
    read_data()
    for key in contents.keys() :
        print(key, contents[key])