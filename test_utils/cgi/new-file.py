# ask the user for the file name
filename = "cgi-out-file.txt"

# ask the user for the file content
content = "mandatory part"

# open the file in write mode
with open(filename, "w") as file:
    # write the content to the file
    file.write(content)

# print a success message
print(f"Successfully created the file '{filename}'")