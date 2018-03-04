from Tkinter import *
from math import sqrt
Rw=1000
Rh=1000

ppu = 1

Xc = Rw/2
Yc = Rh/2

w_screen_max = Xc/ppu
h_screen_max = Yc/ppu
master = Tk()

w = Canvas(master, width=Rw, height=Rh)
w.pack()

def real_to_canvas(x,y):
    return Xc+x*ppu,Yc-y*ppu

def real_to_canvas_x(x):
    return Xc+x*ppu

def real_to_canvas_y(y):
    return Yc-y*ppu

def canvas_to_real(x,y):
    return (x-Xc)/ppu,(Yc-y)/ppu

def canvas_to_real_x(x):
    return (x-Xc)/ppu

def canvas_to_real_y(y):
    return (Yc-y)/ppu

def draw_line(x1,y1,x2,y2):
    global w

    if x1==x2:
        y_max = canvas_to_real_y(0)
        y_min = canvas_to_real_y(Rh)
        w.create_line(
            real_to_canvas(x1,y_min)
            ,real_to_canvas(x1,y_max)
            )
    elif y1==y2:
        x_max = canvas_to_real_x(Rw)
        x_min = canvas_to_real_x(0)
        w.create_line(
            real_to_canvas(x_max,y1)
            ,real_to_canvas(x_min,y1)
            )
    else:

        m=(y2-y1)/(x2-x1)
        b = y1 - m * x1
        x_min = canvas_to_real_x(0)
        y_min = x_min*m+b
        x_max = canvas_to_real_x(Rw)
        y_max = x_max*m+b
        w.create_line(
            real_to_canvas(x_min,y_min),
            real_to_canvas(x_max,y_max)
            )


def draw_segment(x1,y1,x2,y2):
    global w
    w.create_line(
        real_to_canvas(x1,y1),
        real_to_canvas(x2,y2)
    )

def draw_ray(x1,y1,x2,y2):
    global w
    if x1==x2:
        if y1>y2:

            w.create_line(
                real_to_canvas(x1,y1),
                real_to_canvas(x1,canvas_to_real_y(Rh))
            )
        else:
            w.create_line(
                real_to_canvas(x1,y1),
                real_to_canvas(x1,canvas_to_real_y(0))
            )
    elif y1==y2:
        if x1>2:
            w.create_line(
                real_to_canvas(x1,y1),
                real_to_canvas(canvas_to_real_x(0),y1)
            )
        else :
            w.create_line(
                real_to_canvas(x1,y1),
                real_to_canvas(canvas_to_real_x(Rw),y1)
            )
    else : 
        m=(y2-y1)/(x2-x1)
        x_max = canvas_to_real_x(Rw)
        x_min = canvas_to_real_x(0)
        c = y1 - m * x1
        if x1>x2:
            w.create_line(
                    real_to_canvas(x1,y1),
                    real_to_canvas(x_min,x_min*m+c)
                )
        else:
            w.create_line(
                    real_to_canvas(x1,y1),
                    real_to_canvas(x_max,x_max*m+c)
            )

def draw_point(x,y,ray):
    global w
    x1,y1=real_to_canvas(x,y)
    w.create_oval(
        x1+ray,y1+ray,
        x1-ray,y1-ray
    )

with open("out.csv",'r') as f:
    text = f.read()
    for line in text.split('\n'):
        ar = line.split(',')
        if ar[0]=="point" :
            pass
            draw_point(float(ar[1]),float(ar[2]),1)
        elif ar[0]=="line" :
            draw_line(float(ar[1]),float(ar[2]),float(ar[3]),float(ar[4]))
        elif ar[0]=="ray" :
            draw_ray(float(ar[1]),float(ar[2]),float(ar[3]),float(ar[4]))
        else:
            draw_segment(float(ar[1]),float(ar[2]),float(ar[3]),float(ar[4]))


mainloop()