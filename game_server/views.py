from django.http import HttpResponse
from django.shortcuts import render
from environment.Environment import *
from environment.Encoders import Encoder
from django.views.generic.detail import DetailView
import json  


def home(request):
	return render(request,'home.html')


def index(request):
	return render(request,'index.html')


def game(request):
	env = Environment("/server_files/map_init.txt", "/server_files/population_init.txt")
	return HttpResponse(json.dumps(env.reprJson(), cls=Encoder), content_type="application/json")


