from django.http import HttpResponse, Http404
from django.http import HttpRequest
from django.shortcuts import render, render_to_response
from django.template import RequestContext

from environment.Environment import *
from environment.Encoders import Encoder
from django.views.generic.detail import DetailView
import json  


def home(request):
	if request.method == 'GET':
		return render(request, 'home.html')
	elif request.method == 'POST':
		response = render_to_response("404.html")
		response.status_code = 404
		return response


def start_game(request):
	p1_type = request.GET.get('p1_type')
	p2_type = request.GET.get('p2_type')
	print(p1_type)
	print(p2_type)
	env = Environment("/server_files/map_init.txt", "/server_files/population_init.txt")

	return render(request,"game.html", {'data': json.dumps(env.reprJson(), cls=Encoder)})
