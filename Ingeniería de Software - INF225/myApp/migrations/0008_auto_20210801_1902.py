# Generated by Django 3.2.5 on 2021-08-01 23:02

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('myApp', '0007_maquinas'),
    ]

    operations = [
        migrations.DeleteModel(
            name='ReporteAuditoria',
        ),
        migrations.DeleteModel(
            name='ReporteCancelacion',
        ),
        migrations.DeleteModel(
            name='ReporteImpresion',
        ),
        migrations.DeleteModel(
            name='ReporteImpresora',
        ),
        migrations.DeleteModel(
            name='usuario',
        ),
    ]
