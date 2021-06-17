'''
Tester para el Trabajo practico 3. Kuhn 2016
Descripcion: Este programa genera una archivo con un numero aleatoreo de operaciones aleatoreas de precision aleatorea.
Autor: Patricio Tula
'''
import random

#Nombre de los archivos de entrada y salida
OPERATIONS = 'big.in'
RESULTS = 'big.out'

#Constantes para ajustar los archivos de salida
MAX_OPS = 100 #Numero maximo de operaciones
MIN_PREC = 100 #Precision minima
MAX_PREC = 1024 #Precision maxima

OPS = ['+', '*', '-']

def rand_int(n_digits):
	n = random.randint(1, 10**n_digits - 1)
	return -n if random.randint(0,1) > 0 else n

def eval_op(o1, o2, op):
	if op == '+':
		return o1 + o2
	if op == '*':
		return o1 * o2
	if op == '-':
		return o1 - o2

if __name__ == '__main__':
	prec = random.randint(MIN_PREC, MAX_PREC)
	# print 'Using precision = %d' % prec
	with open(OPERATIONS, 'w') as f:
		with open(RESULTS, 'w') as w:
			n = random.randint(1, MAX_OPS)
			for _ in range(n):
				o1 = rand_int(prec)
				o2 = rand_int(prec)
				op = random.choice(OPS)
				line = '%d%s%d\n' % (o1, op, o2)
				outline = '%d\n' % eval_op(o1,o2,op)
				f.write(line)
				w.write(outline)
	w.close()
	f.close()