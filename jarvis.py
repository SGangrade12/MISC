import pyttsx3
import datetime 
import webbrowser
import os
import speech_recognition as sr

engine = pyttsx3.init('sapi5')
voice = engine.getProperty('voices')


def speak(text):
    engine = pyttsx3.init()
    engine.say(text)
    engine.runAndWait()
    engine.stop()

def wishMe():
    hour = int(datetime.datetime.now().hour)
    if hour >= 0 and hour < 12:
        speak("Good Morning Sir")
    elif hour >= 12 and hour < 18:
        speak("Good Afternoon Sir")
    else:
        speak("Good Evening Sir")
    speak("I am Jarvis, your personal assistant. How can I help you today?")
    
def takeCommand():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        r.pause_threshold = 1
        audio = r.listen(source)
    try:
        print("Recognizing...")
        query = r.recognize_google(audio, language='en-in')
        print(f"User said: {query}\n")
    except Exception as e:
        # print(e)
        print("Sorry, I didn't catch that. Please say it again.")
        return "None"
    return query

if __name__=='__main__':
   wishMe()
   takeCommand()