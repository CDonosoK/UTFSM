# Generated by Django 3.2.5 on 2021-08-09 19:39

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('myApp', '0012_remove_maquinas_reservado'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='habilitacion',
            name='id_ayudante',
        ),
        migrations.RemoveField(
            model_name='habilitacion',
            name='id_maker',
        ),
        migrations.AddField(
            model_name='habilitacion',
            name='rutMaker',
            field=models.CharField(default=' ', max_length=100),
            preserve_default=False,
        ),
        migrations.AlterField(
            model_name='recursos',
            name='tipo_maquina',
            field=models.CharField(max_length=100),
        ),
    ]
