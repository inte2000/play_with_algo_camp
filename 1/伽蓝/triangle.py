# dot_list
dot_list = []
for i in range(26):
	dot_list.append(chr(i+65))
	if chr(i+65) == 'K':
		break

# line_list
line_list   = ['ABH','ACGI','ADFJ','AEK','BCDE','EFGH','HIJK']

# init
triangle_number = 0

def IsConnected(p1,p2,line_list):
	for line in line_list:
		if ((p1 in line) & (p2 in line)):
			return True
	else:
		return False

def IsNotSameLine(p1,p2,p3,line_list):
	for line in line_list:
		if (((p1 in line) & (p2 in line) & (p3 in line))):
			return False
	else:
		return True
	
def IsTriangle(p1,p2,p3,line_list):
	global triangle_number
	if (IsConnected(p1,p2,line_list) & IsConnected(p3,p2,line_list) & IsConnected(p1,p3,line_list) & IsNotSameLine(p1,p2,p3,line_list)):
		triangle_number += 1
		print("%d : %s" % (triangle_number,p1+p2+p3))
		return True
	else:
		return False

def Triangle():
	print("Triangles are:")

	for i in dot_list:
		for j in dot_list:
			if j<=i:
				continue
			for k in dot_list:
				if k<=j:
					continue
				IsTriangle(i,j,k,line_list)
				
	print("There are %d triangles in total" % triangle_number)

Triangle()