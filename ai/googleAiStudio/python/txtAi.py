import google.generativeai as genai

genai.configure(api_key="AIzaSyDtOuEoqPTP3WFrtjVKgfm9S3Af-XQbEmw")
model = genai.GenerativeModel("gemini-1.5-flash")
response = model.generate_content("What is Reliability Engineeriing?")
print(response.text)
