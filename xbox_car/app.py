from importlib import import_module
import os
from flask import Flask, render_template, Response
from camera_opencv import Camera

app = Flask(__name__)

@app.route('/')
def index():
    """主页"""
    return render_template('index.html')
    pass


def gen(camera):
    """视频流生成"""
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    """视频流的路线。将其放在img标记的src属性中。"""
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='172.20.10.6', port=9010, threaded=True)

