import random
import numpy as np
from itertools import chain

game_over = False
WIN = 1  # 1: 没有获胜方   2：白棋赢   3：黑棋赢
FREE = 0
USER = 1
ROBOT = 2
PLAY = True  # True:对方AI下棋   False：我方AI下棋

r_scoreLow2 = 20   # 眠二权值
r_scoreHigh2 = 40   # 活二权值
r_scoreLow3 = 60   # 眠三权值
r_scoreHigh3 = 80   # 活三权值
r_scoreLow4 = 100   # 冲四权值
r_scoreHigh4 = 120   # 活四权值
r_scoreHigh5 = 140  # 完成权值
u_scoreLow2 = 10   # 眠二权值
u_scoreHigh2 = 30   # 活二权值
u_scoreLow3 = 50   # 眠三权值
u_scoreHigh3 = 70   # 活三权值
u_scoreLow4 = 90   # 冲四权值
u_scoreHigh4 = 110   # 活四权值
u_scoreHigh5 = 130  # 完成权值

# 棋子状态： 0：空置  1：white 2：black
list_board_status = [[] for i in range(16)]
for i in range(0, 16):
	for j in range(0, 16):
		list_board_status[i].append(0)

def tolistformat(formatlist):  # 二维列表转一维列表
	res = list(chain(*formatlist.tolist()))
	return res

# 黑棋棋型
# 连五：ooooo
R_L5 = [ROBOT, ROBOT, ROBOT, ROBOT, ROBOT]
# 活四：?oooo?
R_L4 = [FREE, ROBOT, ROBOT, ROBOT, ROBOT, FREE]
# 冲四：?oooox  o?ooo  oo?oo
R_S41 = [FREE, ROBOT, ROBOT, ROBOT, ROBOT, USER]
R_S42 = [ROBOT, FREE, ROBOT, ROBOT, ROBOT]
R_S43 = [ROBOT, ROBOT, FREE, ROBOT, ROBOT]
# 活三：?ooo?   o?oo
R_L31 = [FREE, ROBOT, ROBOT, ROBOT, FREE]
R_L32 = [ROBOT, FREE, ROBOT, ROBOT]
# 眠三：??ooox  ?o?oox  ?oo?ox o??oo o?o?o x?ooo?x
R_S31 = [FREE, FREE, ROBOT, ROBOT, ROBOT, USER]
R_S32 = [FREE, ROBOT, FREE, ROBOT, ROBOT, USER]
R_S33 = [FREE, ROBOT, ROBOT, FREE, ROBOT, USER]
R_S34 = [ROBOT, FREE, FREE, ROBOT, ROBOT]
R_S35 = [ROBOT, FREE, ROBOT, FREE, ROBOT]
R_S36 = [USER, FREE, ROBOT, ROBOT, ROBOT, FREE, USER]
# 活二：??oo??  ?o?o?  o??o
R_L21 = [FREE, FREE, ROBOT, ROBOT, FREE, FREE]
R_L22 = [FREE, ROBOT, FREE, ROBOT, FREE]
R_L23 = [ROBOT, FREE, FREE, ROBOT]
# 眠二：???oox  ??o?ox ?o??ox o???o
R_S21 = [FREE, FREE, FREE, ROBOT, ROBOT, USER]
R_S22 = [FREE, FREE, ROBOT, FREE, ROBOT, USER]
R_S23 = [FREE, ROBOT, FREE, FREE, ROBOT, USER]
R_S24 = [ROBOT, FREE, FREE, FREE, ROBOT]

# 白棋棋型
# 连五：ooooo
U_L5 = [USER, USER, USER, USER, USER]
# 活四：?oooo?
U_L4 = [FREE, USER, USER, USER, USER, FREE]
# 冲四：?oooox  o?ooo  oo?oo
U_S41 = [FREE, USER, USER, USER, USER, ROBOT]
U_S42 = [USER, FREE, USER, USER, USER]
U_S43 = [USER, USER, FREE, USER, USER]
# 活三：?ooo?   o?oo
U_L31 = [FREE, USER, USER, USER, FREE]
U_L32 = [USER, FREE, USER, USER]
# 眠三：??ooox  ?o?oox  ?oo?ox o??oo o?o?o x?ooo?x
U_S31 = [FREE, FREE, USER, USER, USER, ROBOT]
U_S32 = [FREE, USER, FREE, USER, USER, ROBOT]
U_S33 = [FREE, USER, USER, FREE, USER, ROBOT]
U_S34 = [USER, FREE, FREE, USER, USER]
U_S35 = [USER, FREE, USER, FREE, USER]
U_S36 = [ROBOT, FREE, USER, USER, USER, FREE, ROBOT]
# 活二：??oo??  ?o?o?  o??o
U_L21 = [FREE, FREE, USER, USER, FREE, FREE]
U_L22 = [FREE, USER, FREE, USER, FREE]
U_L23 = [USER, FREE, FREE, USER]
# 眠二：???oox  ??o?ox ?o??ox o???o
U_S21 = [FREE, FREE, FREE, USER, USER, ROBOT]
U_S22 = [FREE, FREE, USER, FREE, USER, ROBOT]
U_S23 = [FREE, USER, FREE, FREE, USER, ROBOT]
U_S24 = [USER, FREE, FREE, FREE, USER]
ChessType = []

# 黑棋
ChessType.append(R_L5)
ChessType.append(R_L4)
ChessType.append(R_S41)
ChessType.append(R_S42)
ChessType.append(R_S43)
ChessType.append(R_L31)
ChessType.append(R_L32)
ChessType.append(R_S31)
ChessType.append(R_S32)
ChessType.append(R_S33)
ChessType.append(R_S34)
ChessType.append(R_S35)
ChessType.append(R_S36)
ChessType.append(R_L21)
ChessType.append(R_L22)
ChessType.append(R_L23)
ChessType.append(R_S21)
ChessType.append(R_S22)
ChessType.append(R_S23)
ChessType.append(R_S24)
# 白棋
ChessType.append(U_L5)
ChessType.append(U_L4)
ChessType.append(U_S41)
ChessType.append(U_S42)
ChessType.append(U_S43)
ChessType.append(U_L31)
ChessType.append(U_L32)
ChessType.append(U_S31)
ChessType.append(U_S32)
ChessType.append(U_S33)
ChessType.append(U_S34)
ChessType.append(U_S35)
ChessType.append(U_S36)
ChessType.append(U_L21)
ChessType.append(U_L22)
ChessType.append(U_L23)
ChessType.append(U_S21)
ChessType.append(U_S22)
ChessType.append(U_S23)
ChessType.append(U_S24)

ChessWightDict = {}  # 棋型对应的权值
# 黑棋
ChessWightDict[str(R_L5)] = r_scoreHigh5
ChessWightDict[str(R_L4)] = r_scoreHigh4
ChessWightDict[str(R_S41)] = r_scoreLow4
ChessWightDict[str(R_S42)] = r_scoreLow4
ChessWightDict[str(R_S43)] = r_scoreLow4
ChessWightDict[str(R_L31)] = r_scoreHigh3
ChessWightDict[str(R_L32)] = r_scoreHigh3
ChessWightDict[str(R_S31)] = r_scoreLow3
ChessWightDict[str(R_S32)] = r_scoreLow3
ChessWightDict[str(R_S33)] = r_scoreLow3
ChessWightDict[str(R_S34)] = r_scoreLow3
ChessWightDict[str(R_S35)] = r_scoreLow3
ChessWightDict[str(R_S36)] = r_scoreLow3
ChessWightDict[str(R_L21)] = r_scoreHigh2
ChessWightDict[str(R_L22)] = r_scoreHigh2
ChessWightDict[str(R_L23)] = r_scoreHigh2
ChessWightDict[str(R_S21)] = r_scoreLow2
ChessWightDict[str(R_S22)] = r_scoreLow2
ChessWightDict[str(R_S23)] = r_scoreLow2
ChessWightDict[str(R_S24)] = r_scoreLow2
# 白棋
ChessWightDict[str(U_L5)] = u_scoreHigh5
ChessWightDict[str(U_L4)] = u_scoreHigh4
ChessWightDict[str(U_S41)] = u_scoreLow4
ChessWightDict[str(U_S42)] = u_scoreLow4
ChessWightDict[str(U_S43)] = u_scoreLow4
ChessWightDict[str(U_L31)] = u_scoreHigh3
ChessWightDict[str(U_L32)] = u_scoreHigh3
ChessWightDict[str(U_S31)] = u_scoreLow3
ChessWightDict[str(U_S32)] = u_scoreLow3
ChessWightDict[str(U_S33)] = u_scoreLow3
ChessWightDict[str(U_S34)] = u_scoreLow3
ChessWightDict[str(U_S35)] = u_scoreLow3
ChessWightDict[str(U_S36)] = u_scoreLow3
ChessWightDict[str(U_L21)] = u_scoreHigh2
ChessWightDict[str(U_L22)] = u_scoreHigh2
ChessWightDict[str(U_L23)] = u_scoreHigh2
ChessWightDict[str(U_S21)] = u_scoreLow2
ChessWightDict[str(U_S22)] = u_scoreLow2
ChessWightDict[str(U_S23)] = u_scoreLow2
ChessWightDict[str(U_S24)] = u_scoreLow2
# print(ChessWightDict)



class AI:
	def __init__(self, array_status=None):
		self.array_status = array_status
		self.sumScore = {}  # 每个空位置的总得分,初始化为0
		self.linkNum = 4  # 连棋数量，从4开始，7结束
		self.compute()

	def compute_row(self, row, col):
		# 横
		for i in range(0, 16 - self.linkNum):
			if col in range(i, i + self.linkNum):
				typeList = tolistformat(self.array_status[row:row + 1, i:i + self.linkNum])
				typeList[col-i] = ROBOT  # 将空白位置换成黑棋，寻找棋型
				try:
					ChessType.index(typeList)  # 有该棋型
					try:
						self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)], self.sumScore[str((row, col))])  # 记录该坐标的权重
					except KeyError:
						self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
				except ValueError or KeyError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
					typeList[col-i] = USER  # 将空白位置换成白棋，寻找棋型
					try:
						ChessType.index(typeList)  # 有该棋型
						try:
							self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)], self.sumScore[str((row, col))])  # 记录该坐标的权重
						except KeyError:
							self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
					except ValueError or KeyError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
						try:
							self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER), self.sumScore[str((row, col))])
						except KeyError:
							self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER))
			else:
				pass
		# print(self.sumScore)

	def compute_col(self, row, col):
		# 竖
		for i in range(0, 16 - self.linkNum):
			if row in range(i, i + self.linkNum):
				typeList = tolistformat(self.array_status[i:i + self.linkNum, col:col + 1])
				typeList[row-i] = ROBOT  # 将空白位置换成黑棋，寻找棋型
				try:
					# ChessType.index(typeList)  # 有该棋型
					try:
						self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)], self.sumScore[str((row, col))])  # 记录该坐标的权重
					except KeyError:
						self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
				except KeyError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
					typeList[row-i] = USER  # 将空白位置换成白棋，寻找棋型
					try:
						# ChessType.index(typeList)  # 有该棋型
						try:
							self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)],
							                                     self.sumScore[str((row, col))])  # 记录该坐标的权重
						except KeyError:
							self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
					except KeyError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
						try:
							self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER), self.sumScore[str((row, col))])
						except KeyError:
							self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER))
			else:
				pass

	def compute_oblique_l(self, row, col):
		# 左斜 左下对角(10<=row<=14  0<=col<=4)  右上对角(0<=row<=4  10<=col<=14)
		for i in range(0, 16 - self.linkNum):
			for m in range(0, 16 - self.linkNum):
				if (row - i) == (col - m) and row in range(i, i + self.linkNum) and range(m, m + self.linkNum):  # 斜率相同，即在同一条线上，且在选的范围内
					typeList = []
					for k in range(self.linkNum):
						typeList.append(self.array_status[i+k][m+k])
					typeList[row-i] = ROBOT  # 将空白位置换成黑棋，寻找棋型
					try:
						ChessType.index(typeList)  # 有该棋型
						try:
							self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)], self.sumScore[str((row, col))])  # 记录该坐标的权重
						except KeyError:
							self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
					except ValueError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
						typeList[row-i] = USER  # 将空白位置换成白棋，寻找棋型
						try:
							ChessType.index(typeList)  # 有该棋型
							try:
								self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)], self.sumScore[str((row, col))])  # 记录该坐标的权重
							except KeyError:
								self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
						except ValueError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
							try:
								self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER), self.sumScore[str((row, col))])
							except KeyError:
								self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER))
				else:
					pass

	def compute_oblique_r(self, row, col):
		# 右斜
		for i in range(0, 16 - self.linkNum):
			for m in range(self.linkNum, 16):
				if (row - i) == -(col - m) and row in range(i, i + self.linkNum) and range(m - self.linkNum, m):  # 斜率相同，即在同一条线上，且在选的范围内
					typeList = []
					for k in range(self.linkNum):
						typeList.append(self.array_status[i+k][m-k])
					typeList[row-i] = ROBOT  # 将空白位置换成黑棋，寻找棋型
					try:
						ChessType.index(typeList)  # 有该棋型
						try:
							self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)],
							                                     self.sumScore[str((row, col))])  # 记录该坐标的权重
						except KeyError:
							self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
					except ValueError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
						typeList[row-i] = USER  # 将空白位置换成白棋，寻找棋型
						try:
							ChessType.index(typeList)  # 有该棋型
							try:
								self.sumScore[str((row, col))] = max(ChessWightDict[str(typeList)], self.sumScore[str((row, col))])  # 记录该坐标的权重
							except KeyError:
								self.sumScore[str((row, col))] = ChessWightDict[str(typeList)]  # 记录该坐标的权
						except ValueError:  # 没有该棋型， 将权重置为typeList中的黑棋和白棋较多的棋数
							try:
								self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER), self.sumScore[str((row, col))])
							except KeyError:
								self.sumScore[str((row, col))] = max(typeList.count(ROBOT), typeList.count(USER))
				else:
					pass

	def compute(self):
		for row in range(16):
			for col in range(16):
				if self.array_status[row][col] == FREE:  # 计算空位置的最大（横 列 左斜 右斜）权值
					# 4棋子
					self.compute_row(row, col)
					self.compute_col(row, col)
					self.compute_oblique_l(row, col)
					self.compute_oblique_r(row, col)
					# 5棋子
					self.linkNum = 5
					self.compute_row(row, col)
					self.compute_col(row, col)
					self.compute_oblique_l(row, col)
					self.compute_oblique_r(row, col)
					# 6棋子
					self.linkNum = 6
					self.compute_row(row, col)
					self.compute_col(row, col)
					self.compute_oblique_l(row, col)
					self.compute_oblique_r(row, col)
					# 7棋子
					self.linkNum = 7
					self.compute_row(row, col)
					self.compute_col(row, col)
					self.compute_oblique_l(row, col)
					self.compute_oblique_r(row, col)
					# 回到原状态
					self.linkNum = 4
				else:
					pass


class Judge:
	def __init__(self, list_status=None, play=None, chessindex=None):
		self.list_status = list_status  # 棋盘状态
		self.PLAY = play  # True人下白棋1， False机下黑棋2
		self.indexX, self.indexY = chessindex  # 当前放下棋子的坐标
		self.chessNum = 1  # 连棋个数
		self.searchAll = False  # 是否全部搜索完毕
		self.judge = False
		if self.PLAY:  # 现在在下棋的对象
			self.role = USER
		else:
			self.role = ROBOT
		self.main()

	def main(self):
		moveY = self.indexY
		moveX = self.indexX
		direction = True  # 遍历方向 True往右 下， False往左 上
		# 横向5个白棋  x坐标(行)不变
		if not self.searchAll:
			while moveY in range(0, 14):
				if direction:
					moveY += 1
				else:
					moveY -= 1

				if self.list_status[self.indexX][moveY] == self.role:
					self.chessNum += 1
				else:
					# 如果是搜索到左边，则搜索完毕
					if direction is False:
						if self.chessNum < 5:
							self.chessNum = 1  # 搜索完横向，但没有获胜条件，将连棋置为初始状态
							direction = True
							moveY = self.indexY
							moveX = self.indexX
							break
						else:
							pass
					# 只要有一个不匹配，改变方向，且moveX移至起点
					direction = False
					moveY = self.indexY

				if self.chessNum >= 5:
					self.judge = True
					self.searchAll = True
					break
				else:
					pass
		# 竖向5个白棋  y 坐标(列)不变
		if not self.searchAll:
			while moveX in range(0, 14):
				if direction:
					moveX += 1
				else:
					moveX -= 1

				if self.list_status[moveX][self.indexY] == self.role:
					self.chessNum += 1
				else:
					# 如果是搜索到左边，则搜索完毕
					if direction is False:
						if self.chessNum < 5:
							self.chessNum = 1  # 搜索完横向，但没有获胜条件，将连棋置为初始状态
							direction = True
							moveY = self.indexY
							moveX = self.indexX
							break
						else:
							pass
					# 只要有一个不匹配，改变方向，且moveX移至起点
					direction = False
					moveX = self.indexX

				if self.chessNum >= 5:
					self.judge = True
					self.searchAll = True
					break
				else:
					pass
		# 左上到右下斜角
		if not self.searchAll:
			while moveX in range(0, 14) and moveY in range(0, 14):
				if direction:
					moveX += 1
					moveY += 1
				else:
					moveX -= 1
					moveY -= 1

				if self.list_status[moveX][moveY] == self.role:
					self.chessNum += 1
				else:
					# 如果是搜索到左边，则搜索完毕
					if direction is False:
						if self.chessNum < 5:
							self.chessNum = 1  # 搜索完横向，但没有获胜条件，将连棋置为初始状态
							direction = True
							moveY = self.indexY
							moveX = self.indexX
							break
						else:
							pass
					# 只要有一个不匹配，改变方向，且moveX移至起点
					direction = False
					moveX = self.indexX
					moveY = self.indexY

				if self.chessNum >= 5:
					self.judge = True
					self.searchAll = True
					break
				else:
					pass
		# 左下到右上斜角
		if not self.searchAll:
			while moveX in range(0, 14) and moveY in range(0, 14):
				if direction:
					moveX += 1
					moveY -= 1
				else:
					moveX -= 1
					moveY += 1

				if self.list_status[moveX][moveY] == self.role:
					self.chessNum += 1
				else:
					# 如果是搜索到左边，则搜索完毕
					if direction is False:
						if self.chessNum < 5:
							self.chessNum = 1  # 搜索完横向，但没有获胜条件，将连棋置为初始状态
							direction = True
							moveY = self.indexY
							moveX = self.indexX
							break
						else:
							pass
					# 只要有一个不匹配，改变方向，且moveX移至起点
					direction = False
					moveX = self.indexX
					moveY = self.indexY

				if self.chessNum >= 5:
					self.judge = True
					self.searchAll = True
					break
				else:
					pass


def compare(returnAI, index):  # 如果有多个权值相同的点，找出其中里上次下的白棋最近的那个
	AI_max_value = returnAI[max(returnAI, key=returnAI.get)]
	min_dis = 1000
	(rex, rey) = (0, 0)
	for key, val in returnAI.items():
		if val == AI_max_value:
			AI_str = key
			# print(AI_max_value)
			# print(AI_str)
			AI_array = AI_str.split(',')
			str1 = AI_array[0].strip('(')
			str2 = AI_array[1].strip(')').strip(' ')
			x = int(str1)
			y = int(str2)
			if pow(index[0]-x, 2) + pow(index[1]-y, 2) < min_dis:
				min_dis = pow(index[0]-x, 2) + pow(index[1]-y, 2)
				(rex, rey) = (x, y)
	return (rex, rey)



#初始化测试样例
list_eney = [(7,7),(5,7)]
list_all = [(7,7),(6,7),(5,7)]
list_me = [(6,7)]



def ai(list_me,list_eney,list_all):
	# 初始化棋盘情况
	WIN = 1
	PLAY = True
	AIX = 7
	AIY = 7
	for i in range(16):
		for j in range(16):
			list_board_status[i][j] = 0
	for (i,j) in list_me:
		list_board_status[i][j] = 2
	for (i,j) in list_eney:
		list_board_status[i][j] = 1
	# 判断谁先手
	if not list_eney:
		return (7,7)
	else:
		index = list_eney[-1]
		list_board_status[index[0]][index[1]] = 0
		# print("Its last step:{}" . format(index))
		# 交替下棋，并修改棋盘状态
		if list_board_status[index[0]][index[1]] == 0:  # 当前位置没有棋子，才能放下棋子
			# 实现AI： 获取合理的 index[0] 和 index[1]
			list_board_status_array = np.array(list_board_status)
			ComputeAI = AI(list_board_status_array)
			AIX, AIY = compare(ComputeAI.sumScore, index)  # 优化返回的坐标值，选择相同权值中离上一步白棋坐标最近的那个位置
			list_board_status[AIX][AIY] = ROBOT
			list_me.append((AIX,AIY))
			list_all.append((AIX,AIY))
			# print("My step:({aix},{aiy})" . format(aix=AIX,aiy=AIY))
			# print("list_me:{}" . format(list_me))
			# print("list_eney:{}" . format(list_eney))
			# print("list_all:{}" . format(list_all))
			return (AIX,AIY)

# print(ai(list_me,list_eney,list_all))