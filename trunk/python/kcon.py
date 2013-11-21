from Tkinter import *
from hotkey import Hotkey
# import hotkey
import win32api
import win32con
import win32gui

def echo(str):
	win32api.MessageBox(0,str, "title")

class kcon():
	"""A keybord control program"""
	def __init__(self):
		hCheck = win32gui.FindWindow(None, 'kcon')
		if hCheck > 0:
			echo('Program has been running')
		else:
			self.root = Tk()
			self.root.title('kcon')
			hwnd = self.root.winfo_id()
			self.box = self.TaskList(self.root)
			self.edit = self.EditLine(self.root, self.box)
			self.root.bind_all('<Control-Key-a>', self.onCtrlA)
			self.root.bind_all("<Key>", self.onPress)
			self.root.bind_all('<Return>',	self.onReturn)
			self.hotkey = Hotkey(self.root)
			self.root.mainloop()	

	def onCtrlA(self, event):
		self.edit.clear()
		self.box.flush('')
		self.edit.focus()

	def onPress(self, event):
		if event.keysym == 'Escape':
			# self.root.quit()
			hTop = win32gui.GetForegroundWindow()
			win32gui.ShowWindow(hTop, win32con.SW_MINIMIZE)
		elif event.keysym == 'Up':
			self.box.focus()
		elif event.keysym == 'Down':
			self.box.focus()
		else:
			contents = self.edit.get()
			self.box.flush(contents)
	def onReturn(self, event):
		hwnd = win32gui.GetForegroundWindow()
		hwnd = self.box.getHwnd()
		win32gui.ShowWindow(hwnd, win32con.SW_RESTORE)
		win32gui.SetForegroundWindow(hwnd)

	class TaskList():
		"""docstring for TaskList"""
		def __init__(self, root):
			self.root = root
			self.list = Listbox(root, height=20)
			self.list.pack(fill = BOTH, side=BOTTOM)
			self.process_list = {}
			self.search = ""
			self.i = 0
			win32gui.EnumWindows(self.enumHandler, None)
			for pos in self.process_list:
				self.insert(pos, self.process_list[pos]["text"])

		def insert(self, index, text):
			self.list.insert(index, text)

		def clear(self):
			self.i = 0
			self.process_list = {}
			self.list.delete(0, END)

		def enumHandler(self, hwnd, lParam):
			if win32gui.IsWindowVisible(hwnd):
				title = win32gui.GetWindowText(hwnd).decode("gbk")
				if self.search.lower() in title.lower():
					self.process_list[self.i] = {}
					self.process_list[self.i]["text"] = title
					self.process_list[self.i]["hwnd"] = hwnd
					self.i = self.i + 1
		def flush(self, contents):
			global i, search, process_list
			self.search = contents
			self.clear()		
			win32gui.EnumWindows(self.enumHandler, None)
			for pos in self.process_list:
				self.insert(pos, self.process_list[pos]["text"])
			self.list.selection_set(0)

		def focus(self):
			self.list.focus_set()

		def getHwnd(self):
			(cur, ) = self.list.curselection()
			hwnd = self.process_list[int(cur)]['hwnd']
			return hwnd

	class EditLine():
		"""docstring for EditLine"""
		def __init__(self, root, listbox):
			self.root = root
			self.listbox = listbox
			self.text = Entry(root, width=200)
			self.text.pack(fill = BOTH, side=TOP)
			self.text.focus_set()
			# self.text.bind('<Key-1>',	self.test)
			# text.bind("<BackSpace>", Press)
		def test(self, event):
			echo('1')
		def get(self):
			return self.text.get()
		def clear(self):
			self.text.delete(0, END)
		def focus(self):
			self.text.focus_set()



if __name__ == "__main__":
    app = kcon()