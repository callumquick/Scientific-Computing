import pyperclip as clip

text = clip.paste()
print(text)
lines = text.split("\n")
for i in range(len(lines)):
    lines[i] = "* " + lines[i]
newtext = "\n".join(lines)
clip.copy(newtext)
print("converted to:")
print(newtext)
