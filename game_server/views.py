from django.http import HttpResponse, Http404
from django.http import HttpRequest
from django.shortcuts import render, render_to_response
from django.template import RequestContext
from django.views.decorators.csrf import csrf_exempt
from environment.Environment import *
from environment.Encoders import Encoder
from django.views.generic.detail import DetailView
from game_server.controllers import Controller
import json


__controller = -1

def home(request):
    return render(request, 'index.html')


def new_game(request):
    if request.method == 'POST':
        p1_type = request.POST.get('p1_type')
        p2_type = request.POST.get('p2_type')
        global __controller
        __controller = Controller(p1_type, p2_type)
        return HttpResponse(json.dumps(json.dumps(__controller.env.reprJson(), cls=Encoder)), content_type="application/json")


def deploy_human(request):
    #controller = request.session['controller']
    target = request.POST.get('target')
    count = request.POST.get('count')
    try:
        global __controller
        __controller.deploy(target, count)
        return HttpResponse(json.dumps({'success': 1, 'msg': 'good'}), content_type="application/json")
    except Exception as e:
        return HttpResponse(json.dumps({'success': 0, 'msg': str(e)}), content_type="application/json")
    request.session.modified = True


def get_start_page(request):
    return render(request, 'start_page.html')


def get_start_modal(request):
    return render(request, 'start_modal.html')


def get_gameplay_page(request):
    return render(request, 'gameplay_page.html')


def get_control_panel(request):
    return render(request, 'control_panel.html')


def get_game_canvas(request):
    return render(request, 'game_canvas.html')


def get_winner_modal(request):
    return render(request, 'winner_modal.html')
