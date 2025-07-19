# filepath: /home/jacob-muema/Documents/flask/AI/devops-youtube/ai/googleAiStudio/python/app.py
from flask import Flask, request, render_template
import google.generativeai as genai

app = Flask(__name__)

# Configure the Generative AI API
genai.configure(api_key="AIzaSyDtOuEoqPTP3WFrtjVKgfm9S3Af-XQbEmw")
model = genai.GenerativeModel("gemini-1.5-flash")

@app.route("/", methods=["GET", "POST"])
def index():
    response_text = ""
    if request.method == "POST":
        user_input = request.form["user_input"]
        response = model.generate_content(user_input)
        response_text = response.text
    return render_template("index.html", response_text=response_text)

if __name__ == "__main__":
    app.run(debug=True)