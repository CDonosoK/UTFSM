# Generated by Django 3.2.5 on 2021-07-12 00:57

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('myApp', '0005_reportecancelacion'),
    ]

    operations = [
        migrations.RenameField(
            model_name='reporteauditoria',
            old_name='workgroup_name',
            new_name='date',
        ),
        migrations.RenameField(
            model_name='reportecancelacion',
            old_name='impresora',
            new_name='account_email',
        ),
        migrations.RenameField(
            model_name='reportecancelacion',
            old_name='usuario',
            new_name='cancel_by',
        ),
        migrations.RenameField(
            model_name='reporteimpresion',
            old_name='usuario',
            new_name='account',
        ),
        migrations.RenameField(
            model_name='reporteimpresora',
            old_name='impresora',
            new_name='account',
        ),
        migrations.RenameField(
            model_name='reporteimpresora',
            old_name='workgroup_name',
            new_name='client_version',
        ),
        migrations.RemoveField(
            model_name='reporteauditoria',
            name='text',
        ),
        migrations.RemoveField(
            model_name='reportecancelacion',
            name='text',
        ),
        migrations.RemoveField(
            model_name='reporteimpresion',
            name='text',
        ),
        migrations.RemoveField(
            model_name='reporteimpresora',
            name='text',
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='email',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='estimated_printer_h',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='file_name',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='job_id',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='material_cost',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='material_used',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='printer_id',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='real_print_h',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteauditoria',
            name='status',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reportecancelacion',
            name='cancel_details',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reportecancelacion',
            name='cancel_reasons',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reportecancelacion',
            name='client_version',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reportecancelacion',
            name='file_id',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reportecancelacion',
            name='job_id',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reportecancelacion',
            name='printer_name',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reportecancelacion',
            name='printer_type',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresion',
            name='last_print_date_time',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresion',
            name='material_cost',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresion',
            name='material_used_kg',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresion',
            name='print_errors',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresion',
            name='prints',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresion',
            name='real_print_time_h',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='host',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='last_print_date_time',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='material_cost',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='material_used_kg',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='online_offline',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='print_errors',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='printer_id',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='printer_name',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='printer_type',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='printer_vid',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='prints',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='real_print_time_h',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='reporteimpresora',
            name='status',
            field=models.CharField(default=0, max_length=100),
            preserve_default=False,
        ),
    ]
