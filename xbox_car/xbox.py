import pygame
import time



class xbox_(object):

    def __init__(self, time_read):
        self.data_pack = [0 for i in range(24)]

        self.L_UP_DOWN = 0
        self.L_LEFT_RIGHT = 0
        self.R_UP_DOWN = 0
        self.R_LEFT_RIGHT = 0
        self.R_UP = 0
        self.L_UP = 0
        self.A_BUTTON = 0
        self.B_BUTTON = 0
        self.X_BUTTON = 0
        self.Y_BUTTON = 0
        self.START_BUTTON = 0
        self.BACK_BUTTON = 0
        self.LOGITECH_BUTTON = 0
        self.LEFT_GA_BUTTON = 0
        self.RIGHT_GA_BUTTON = 0
        self.LB_BUTTON = 0
        self.RB_BUTTON = 0
        self.FX_RIGHT = 0
        self.FX_LEFT = 0
        self.FX_UP = 0
        self.FX_DOWN = 0

        self.done=False
        self.time = time_read


    def clean_button(self):
        self.A_BUTTON = 0
        self.B_BUTTON = 0
        self.X_BUTTON = 0
        self.Y_BUTTON = 0
        self.START_BUTTON = 0
        self.BACK_BUTTON = 0
        self.LOGITECH_BUTTON = 0
        self.LEFT_GA_BUTTON = 0
        self.RIGHT_GA_BUTTON = 0
        self.LB_BUTTON = 0
        self.RB_BUTTON = 0
        self.FX_RIGHT = 0
        self.FX_LEFT = 0
        self.FX_UP = 0
        self.FX_DOWN = 0
        self.L_UP_DOWN = 0
        self.L_LEFT_RIGHT = 0
        self.R_UP_DOWN = 0
        self.R_LEFT_RIGHT = 0



    def stop(self):
        
        self.done = True

    def ToInt_3(self, num):
        return int(num * 100) + 100
    
    def print_data(self):
        print('L_Left/Right:', self.L_LEFT_RIGHT)
        print('L_up/dowm:', self.L_UP_DOWN)
        print('R_Left/Right:', self.R_LEFT_RIGHT)
        print('R_up/dowm:', self.R_UP_DOWN)
        print('A_BUTTON:', self.A_BUTTON)
        print('B_BUTTON:', self.B_BUTTON)
        print('X_BUTTON:', self.X_BUTTON)
        print('Y_BUTTON:', self.Y_BUTTON)
        print('START_BUTTON:', self.START_BUTTON)
        print('BACK_BUTTON:', self.BACK_BUTTON)
        print('LOGITECH_BUTTON:', self.LOGITECH_BUTTON)
        print('LEFT_GA_BUTTON:', self.LEFT_GA_BUTTON)
        print('RIGHT_GA_BUTTON:', self.RIGHT_GA_BUTTON)
        print('FX_UP:', self.FX_UP)
        print('FX_DOWN:', self.FX_DOWN)
        print('FX_LEFT:', self.FX_LEFT)
        print('FX_RIGHT:', self.FX_RIGHT)
        print('L_UP:',self.L_UP)
        print('R_UP:',self.R_UP)
        print('LB_BUTTON:',self.LB_BUTTON)
        print('RB_BUTTON:',self.RB_BUTTON)


    def pack(self, xbox_pack):
        self.data_pack = [
            85,
            self.L_UP_DOWN ,

            self.L_LEFT_RIGHT ,
            self.R_UP_DOWN ,
            self.R_LEFT_RIGHT ,
            self.L_UP ,
            self.R_UP ,
            self.A_BUTTON ,
            self.B_BUTTON ,
            self.Y_BUTTON ,
            self.X_BUTTON ,
            self.START_BUTTON ,
            self.BACK_BUTTON ,
            self.LOGITECH_BUTTON ,
            self.LEFT_GA_BUTTON ,
            self.RIGHT_GA_BUTTON ,
            self.LB_BUTTON ,
            self.RB_BUTTON ,
            self.FX_LEFT ,
            self.FX_RIGHT ,
            self.FX_UP ,
            self.FX_DOWN ,
            13,
            10
            ]
        
        for i in range(24):
            xbox_pack[i] = self.data_pack[i]
    def send_pack(self):
        pass

    def xbox_run(self, xbox_pack):
        pygame.init()
        pygame.joystick.init()
        
        while (self.done != True):
            time.sleep(self.time)
            for event in pygame.event.get():  # User did something
                if event.type == pygame.QUIT:  # If user clicked close
                    self.done = True  # Flag that we are done so we exit this loop

            # ----------------------------------------------------------------
            joystick_count = pygame.joystick.get_count()
            # self.print_data()
            self.pack(xbox_pack)
            self.clean_button()
            
            for i in range(joystick_count):
                joystick = pygame.joystick.Joystick(i)
                joystick.init()
                axes = joystick.get_numaxes()
                for i in range(axes):
                    axis = joystick.get_axis(i)
                    if i == 0:  
                        self.L_LEFT_RIGHT = self.ToInt_3(axis)
                    elif i == 1:
                        self.L_UP_DOWN = self.ToInt_3(axis)

                    elif i == 2:
                        self.R_LEFT_RIGHT = self.ToInt_3(axis)

                    elif i == 3 :
                        self.R_UP_DOWN = self.ToInt_3(axis)

                    elif i == 4:
                        self.L_UP = self.ToInt_3(axis)

                    elif i == 5:
                        self.R_UP = self.ToInt_3(axis)


            #- ----------------------------------------------------------------
            buttons = joystick.get_numbuttons()
            for i in range( buttons ):
                button = joystick.get_button( i )
                if i==0 and button ==1:

                    self.A_BUTTON = 1
                if i==1 and button ==1:

                    self.B_BUTTON = 1
                if i==2 and button ==1:

                    self.X_BUTTON = 1
                if i==3 and button ==1:
  
                    self.Y_BUTTON = 1
                if i==4 and button ==1:
    
                    self.LB_BUTTON = 1
                if i==5 and button ==1:
     
                    self.RB_BUTTON = 1
                if i==6 and button ==1:
      
                    self.BACK_BUTTON = 1
                    # self.stop()
                if i==7 and button ==1:
             
                    self.START_BUTTON = 1
                if i==8 and button ==1:
      
                    self.LEFT_GA_BUTTON = 1
                if i==9 and button ==1:
      
                    self.RIGHT_GA_BUTTON = 1
                if i==10 and button ==1:
      
                    self.LOGITECH_BUTTON = 1

            #----------------------------------------------------------------
            hats = joystick.get_numhats()
            for i in range( hats ):
                hat = joystick.get_hat( i )
                if hat==(1,0) :

                    self.FX_RIGHT = 1
                if hat==(-1,0) :

                    self.FX_LEFT = 1
                if hat==(0,1):

                    self.FX_UP = 1
                if hat==(0,-1):

                    self.FX_DOWN = 1

xbox = xbox_(time_read = 0.1)

def read_xbox(time_read, xbox_pack):
    global xbox
    # xbox = xbox_(time_read = time_read)
    xbox.xbox_run(xbox_pack)

