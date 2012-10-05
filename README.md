From the CSE Assignment Lab 4 page

The objective for this assignment is to implement the Program_Generate_Code component, which is an extension to the Program component.

You will be implementing the Generate_Code operation as an extension to the Program component (see the Program section in the class notes for the specs). Your implementation will translate a Program object into the corresponding code for the BugsWorld virtual machine (discussed in class). This is the last phase in the BL translator.

In addition, your implementation will also check for the few possible remaining syntax errors, which were not checked by the parser. These include undefined instructions and direct and/or indirect use of recursion. Use the assert statement to notify users of these errors, just as you did in the previous lab assignment.

