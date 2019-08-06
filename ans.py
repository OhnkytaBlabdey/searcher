import pickle
import random
from math import *


class Node(object):
	"""docstring for Node"""
	def __init__(self, parent = None, child_count = None):
		super(Node, self).__init__()

		self.visited = 0
		self.parent = parent
		self.count_child = child_count or 0
		self.count_descendant = child_count or 0

		if child_count is not None:
			if not type(child_count) is int or child_count < 1:
				print('Error : cannot add', child_count, 'childs')
				raise AssertionError
			self.childs = [Node(parent = self) for x in range(child_count)]
			self.have_child = True
		else:
			self.childs = []
			self.have_child = None

	def containsChildren(self):
		return self.have_child

	def countChildren(self):
		if self.have_child:
			return self.count_child
		else:
			print('Error : children count not determined or have no children.')
			print(self)
			raise AssertionError

	def countDescendant(self):
		"""not include self"""
		if self.have_child is None:
			print('Error : children count not determined.')
			raise AssertionError
		elif self.have_child == False:
			return 0
		return self.count_descendant

	def getSon(self, i):
		if not self.have_child:
			print('Error : children count not determined or have no children.')
			raise AssertionError
		elif type(i) is not int:
			print('Error : ', i, 'have a type', type(i))
			raise AssertionError
		elif i > self.count_child:
			print(self, 'have only', self.count_child, 'child, but attempt to index its ', i, 'th child')
			raise AssertionError
		elif self.count_child != len(self.childs):
			print('Error : check error', self.count_child, len(self.childs))
			raise AssertionError
		# self.visit()
		return self.childs[i - 1]

	def addSon(self, m):
		if self.have_child is not None or self.childs != []:
			print('Error :', self, 'already has', self.have_child, ' children :', self.childs)
			raise AssertionError
		elif type(m) is not int:
			print('Error : ', m, 'have a type', type(m))
			raise AssertionError
		elif m <= 1:
			self.have_child = False
			self.destroy() # auto detect
			return
		self.childs = [Node(parent = self) for x in range(m)]
		self.have_child = True
		self.count_child = m
		self.count_descendant = m

		p = self.parent
		while p is not None:
			p.count_descendant += m
			p = p.parent

	def getParent(self):
		return self.parent

	def getVisited(self):
		return self.visited
	def visit(self):
		self.visited += 1

	def countUnVisitedDescendant(self):
		if not self.have_child:
			return 0
		pass

	def remove(self, child):
		if not self.have_child:
			print('Error : no children to remove')
			raise AssertionError
		elif child not in self.childs:
			print('Error :', child, 'not in ', self.childs)
			raise AssertionError
		self.childs.remove(child)
		self.count_child -= 1
		delt = child.countDescendant() + 1
		self.count_descendant -= delt
		p = self.parent
		while p is not None:
			p.count_descendant -= delt
			p = p.parent

	def destroy(self):
		p = self.getParent()
		if p is None:
			return
		p.remove(self)
		# del self
		while p is not None:
			if p.childs == []:
				q = p
				p = p.getParent()
				if p is not None:
					q.destroy()
				# else: p == root
			else:
				break
		del self



root = Node()
root.addSon(2)
node = root.getSon(1)
node.addSon(9)
node.getSon(8).addSon(0)
# node.getSon(8).destroy()
# node.getSon(9)
print(node.countDescendant())
print(root.countDescendant())
# node.destroy()
# root.getSon(2)