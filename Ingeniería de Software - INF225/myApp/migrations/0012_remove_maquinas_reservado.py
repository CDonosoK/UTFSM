# Generated by Django 3.2.5 on 2021-08-07 18:23

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('myApp', '0011_maquinas_reservado'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='maquinas',
            name='reservado',
        ),
    ]
