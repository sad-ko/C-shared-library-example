# [DATA-PLUG] - A C example of how to utilize shared libraries

## About this program
#### What is [DATA-PLUG]?
[DATA-PLUG] is a sort of simplified data fetcher from databases installed as plugins.

#### What is [DATA-PLUG] propose?
[DATA-PLUG] is a somewhat easy example of how to use shared libraries while showing the benefits of them. 

#### How exactly does it achieve that?
This example utilizes the ability of dynamically loaded library as plugins for our program, with the benefit of adding functionality to it.


## The logic behind
Every database API is installed as a **.plugin** (how to compile them as this is shown in the Makefile) inside the **plugins** folder, their APIs are limited only to these functions: **[get_info, get_name]**.


### **[get_info]:** 
Its declaration is as follow: `char* get_info(const char* search) `

It should find all the information related to the searched word and formated as desired, but it must be returned as a string allocated in the heap (for this we have the handy macro **create_string** insde the header **plugins.h**).

### **[get_name]:** 
Its declaration is as follow: `char* get_name() `

Its only purpose is to return the database name.

## TODO
- More documentation.
