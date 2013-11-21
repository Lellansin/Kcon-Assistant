import os, sys, ctypes
from ctypes import wintypes
import win32con
import thread
import win32api
import win32gui

def echo(str):
	win32api.MessageBox(0,str, "title")

byref = ctypes.byref
user32 = ctypes.windll.user32

HOTKEYS = {
	1 : (win32con.VK_F3, win32con.MOD_CONTROL),
	2 : (win32con.VK_F4, win32con.MOD_CONTROL),
	3 : (win32con.VK_F8, win32con.MOD_CONTROL)
}

def handle_win_f3 ():
	os.startfile (os.environ['TEMP'])

def handle_win_f4 ():
	echo('hello')
	# user32.PostQuitMessage (0)

def hello():
	echo('hello')

HOTKEY_ACTIONS = {
	1 : handle_win_f3,
	2 : handle_win_f4,
}

class Hotkey():
	"""docstring for Hotkey"""
	def __init__(self, root):
		self.root = root
		HOTKEY_ACTIONS[3] = self.back
		try:
			thread.start_new_thread( self.MessageLoop, () )
		except:
			print "Error: unable to start thread"

	def back(self):
		# echo('hello ctrl k')
		hMain = win32gui.FindWindow(None, 'kcon')
		hTop = win32gui.GetForegroundWindow()
		if hTop == hMain:
			win32gui.ShowWindow(hMain, win32con.SW_MINIMIZE)
		else:
			win32gui.ShowWindow(hMain, win32con.SW_RESTORE)
			win32gui.SetForegroundWindow(hMain)

	def addHotKey(self):
		pass

	def MessageLoop(self):
		for id, (vk, modifiers) in HOTKEYS.items ():
			print "Registering id", id, "for key", vk
			if not user32.RegisterHotKey (None, id, modifiers, vk):
				print "Unable to register id", id
		try:
			msg = wintypes.MSG()
			while user32.GetMessageA(byref (msg), None, 0, 0) != 0:
				if msg.message == win32con.WM_HOTKEY:
					action_to_take = HOTKEY_ACTIONS.get (msg.wParam)
					if action_to_take:
						action_to_take()
				user32.TranslateMessage(byref (msg))
				user32.DispatchMessageA(byref (msg))
		finally:
			for id in HOTKEYS.keys ():
				user32.UnregisterHotKey(None, id)