"""game_server URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""

from django.contrib import admin
from django.urls import path
from . import views
from django.contrib.staticfiles.urls import staticfiles_urlpatterns

handler404 = 'game_server.views.handler404'

urlpatterns = [
    path('admin/', admin.site.urls),
    path('home/', views.home),

    path('new_game', views.new_game),
    path('deploy_human', views.deploy_human),
    path('march_human', views.march_human),
    path('invade_human', views.invade_human),
    path('home/components/start_page/start_page.html', views.get_start_page),
    path('home/components/start_page/start_modal.html', views.get_start_modal),
    path('home/components/gameplay_page/gameplay_page.html', views.get_gameplay_page),
    path('home/components/gameplay_page/control_panel.html', views.get_control_panel),
    path('home/components/gameplay_page/game_canvas.html', views.get_game_canvas),
    path('home/components/gameplay_page/winner_modal.html', views.get_winner_modal),
   # path('invade_human/', views.invade_human),
   # path('deploy_agent/', views.deploy_agent),
   # path('march_agent/', views.march_agent),
   # path('invade_agent/', views.invade_agent),
]

urlpatterns += staticfiles_urlpatterns()