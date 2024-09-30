def is_valid_parentheses(s):
    stack = []
    mapping = {")": "(", "}": "{", "]": "["}
    for char in s:
        if char in mapping.values():
            stack.append(char)
        elif char in mapping.keys():
            if stack == [] or mapping[char] != stack.pop():
                return "no"
        else:
            return "no"
    return "yes" if stack == [] else "no"
# Đoạn code dưới đây sẽ đọc xâu đầu vào và gọi hàm kiểm tra
if __name__ == "__main__":
    input_string = input().strip()
    print(is_valid_parentheses(input_string))
