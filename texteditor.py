#
#   Vladislav Zolotukhin -  A simple text editor code in Python
#                           Allows for font and colour customization
#                           Supports file reading and writing
#   2024-10-14
#


import os
from tkinter import *
from tkinter import filedialog, colorchooser, font
from tkinter.messagebox import *
from tkinter.filedialog import *


def change_color():
    color = colorchooser.askcolor(title="Select a color")
    print(color) #color will be a tuple -> (R,G,B), Hex
    text_area.config(fg=color[1])

def change_font(args): #either the font style or font size will call this, so the amount of arguments will vary
    text_area.config(font=(font_name.get(), size_box.get()))

def new_file():
    window.title("Untitled") #default name for a new file
    text_area.delete(1.0, END) #range uses floating points, delete everything

def open_file():
    file = askopenfilename(defaultextension=".txt", file=[("All files", "*.*"), ("Text Documents", "*.txt")])
    try:
        window.title=(os.path.basename(file)) # sets the window title to the name of the opened file
        text_area.delete(1.0, END) #clear the current text area
        file = open(file, "r") # open file for reading
        text_area.insert(1.0, file.read()) #add the text contents of the opened file to the text area
    except Exception:
        print("Couldn't read file") # generic error
    finally:
        file.close() # remember to always close the file at the end !

def save_file():
    file = filedialog.asksaveasfilename(initialfile="untitled.txt", defaultextension=".txt", filetypes=[("All files", "*.*"), ("Text Documents", "*.txt")]) #default filename to save as
    if file is None: # if user closes out of the file dialog w/o saving
        return
    else:
        try:
            # create a new file with the specified name and path from above, open it for writing, add all of the contexts of the text area
            window.title(os.path.basename(file))
            file = open(file, "w")
            file.write(text_area.get(1.0, END))
        except Exception:
            print("Saving failed!")
        finally:
            file.close()

def cut():
    text_area.event_generate("<<Cut>>")

def copy():
    text_area.event_generate("<<Copy>>")

def paste():
    text_area.event_generate("<<Paste>>")

def about():
    showinfo("About This Program", "Created by Vladislav Zolotukhin 2024-10-14") #title, text

def quit():
    window.destroy() # close the window


window = Tk()
window.title("Text editor in Python")

file = None

window_width = 500
window_height = 500

# To center the text editor window
screen_width = window.winfo_screenwidth()
screen_height = window.winfo_screenheight()
x = int((screen_width / 2) - (window_width / 2))
y = int((screen_height / 2) - (window_height / 2))
window.geometry("{}x{}+{}+{}".format(window_width, window_height, x, y))

font_name = StringVar(window)
font_name.set("Arial")
font_size = StringVar(window)
font_size.set("25")

text_area = Text(window, font = (font_name.get(),font_size.get()))
scroll_bar = Scrollbar(text_area) # add a scroll bar to the text area
window.grid_rowconfigure(0, weight = 1)
window.grid_columnconfigure(0, weight = 1)
text_area.grid(sticky=N + E + S + W) # the text area encompasses the entire window

scroll_bar.pack(side=RIGHT, fill=Y)
text_area.config(yscrollcommand=scroll_bar.set)


frame = Frame(window)
frame.grid()

color_button = Button(frame, text="Color", command=change_color)
color_button.grid(row=0, column=0)
font_box = OptionMenu(frame, font_name, *font.families(), command=change_font) #adds all of the different available fonts by unpacking (*) font.families
font_box.grid(row=0, column = 1)

size_box = Spinbox(frame, from_=1, to=100, textvariable=font_size, command=change_font) #from needs an underscore
size_box.grid(row=0, column=2)

# Creating a File, Edit, & Help menu
menu_bar = Menu(window)
window.config(menu = menu_bar)
# The file menu
file_menu = Menu(menu_bar, tearoff=0) #tearoff is just a default dotted line on the top of the menu
menu_bar.add_cascade(label="File", menu=file_menu)
file_menu.add_command(label="New", command=new_file)
file_menu.add_command(label="Open", command=open_file)
file_menu.add_command(label="Save", command=save_file)
file_menu.add_separator()
file_menu.add_command(label="Exit", command=quit)

edit_menu = Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="Edit", menu=edit_menu)
edit_menu.add_command(label="Cut", command=cut)
edit_menu.add_command(label="Copy", command=copy)
edit_menu.add_command(label="Paste", command=paste)

help_menu = Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="Help", menu=help_menu)
help_menu.add_command(label="About", command=about)


window.mainloop()