# Generated by Django 4.2.3 on 2023-07-17 04:46

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('sub_licensing', '0001_initial'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='subscription',
            name='valid_until',
        ),
        migrations.AlterField(
            model_name='subscription',
            name='activation_date',
            field=models.DateTimeField(auto_now_add=True),
        ),
    ]
