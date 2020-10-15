

from collections import Counter as COUNTER

# Sort dictionary based on values
def sort_dictionary(info, reverse=True, display=False):
	result = COUNTER(info).most_common()
	if reverse is False:
		result = result[::-1]
	return result
	if display is True:
		for key, val in result:
			print "Key: %s Val: %s" % (key, val)

# Get most frequent words from file
def frequent_words(filename, count):
	info = dict()
	with open(filename) as fileobj:
		lines = fileobj.readlines()
		for line in lines:
			words = line.split()
			for word in words:
				frequency = info.get(word, 0)
				frequency = frequency + 1
				info[word] = frequency
	result = sort_dictionary(info)
	for values in result:
		if count == 0:
			break
		else:
			print "Word: %s Frequency: %d" % (values[0], values[1])
			count = count - 1

# Reverse characters of word
def reverse_word(strarg):
	print "Input:\t'%s'" % strarg	
	chars = list(strarg)
	strout = "".join(reversed(chars))
	print "Output:\t'%s'" % strout
	return strout	

# Reverse words of sentence include whitespaces
def reverse_sentence(strarg):
	print "Input:\t'%s'" % strarg
	strout = " ".join(reversed(strarg.split(' ')))
	print "Output:\t'%s'" % strout
	return strout


def try_test(strval):
	try: 
		intval = int(strval)
		print("Integer Value: %d" % intval)
	except:
		print("Exception occured")


# Main function
def main():
	# sentence = "Time  is Money"
	# reverse_sentence(sentence)	

	# word = "Test"
	# reverse_word(word)

	info = {"Nitin" : 1, "Sachin" : 3, "Sneha" : 2}
	sort_dictionary(info, True)

	frequent_words("/tmp/text.log", 5)
	try_test("-1")

# Execute function
if __name__ == '__main__':
	main()
