create schema bstu;

alter schema bstu owner to postgres;

create table languages
(
	id serial not null
		constraint languages_pk
			primary key,
	name varchar not null
);

alter table languages owner to postgres;

create unique index languages_id_uindex
	on languages (id);

create table achievements_types
(
	id serial not null
		constraint achievements_types_pk
			primary key,
	name varchar,
	points integer not null
);

alter table achievements_types owner to postgres;

create table achievements
(
	code integer not null
		constraint achievements_pk
			primary key,
	type integer
		constraint achievements_achievements_types_id_fk
			references achievements_types,
	given_by varchar not null,
	name varchar
);

alter table achievements owner to postgres;

create unique index achievements_code_uindex
	on achievements (code);

create unique index achievements_types_id_uindex
	on achievements_types (id);

create table specialities
(
	id serial not null
		constraint specialities_pk
			primary key,
	name varchar,
	institute_name varchar,
	parent_spec integer,
	institute_id integer,
	level integer,
	code varchar,
	spec_id integer
);

alter table specialities owner to postgres;

create unique index specialities_id_uindex
	on specialities (id);

create table exam_subjects
(
	id serial not null
		constraint exam_subjects_pk
			primary key,
	name varchar
);

alter table exam_subjects owner to postgres;

create unique index exam_subjects_id_uindex
	on exam_subjects (id);

create table orders
(
	id serial not null
		constraint orders_pk
			primary key,
	name varchar,
	date date,
	wave integer
);

alter table orders owner to postgres;

create unique index orders_id_uindex
	on orders (id);

create table campaign
(
	id serial not null
		constraint campaign_pk
			primary key,
	name varchar
);

alter table campaign owner to postgres;

create table abiturients
(
	id serial not null
		constraint abiturients_pk
			primary key,
	name varchar not null,
	surname varchar not null,
	thirdname varchar,
	phone_number varchar,
	dorm_needed boolean,
	gender char not null,
	language_id integer not null
		constraint abiturients_languages_id_fk
			references languages
				on update cascade,
	low_points boolean default false not null,
	email varchar,
	campaign_id integer
		constraint abiturients_campaign_id_fk
			references campaign
);

alter table abiturients owner to postgres;

create unique index abiturients_id_uindex
	on abiturients (id);

create table personal_documents
(
	id serial not null
		constraint personal_documents_pk
			primary key,
	serial integer not null,
	number integer,
	given_by varchar not null,
	date date default '2000-06-06'::date not null,
	place_of_birth varchar not null,
	type varchar,
	abit_id integer not null
		constraint personal_documents_abiturients_id_fk
			references abiturients
				on update cascade
);

alter table personal_documents owner to postgres;

create unique index personal_documents_id_uindex
	on personal_documents (id);

create table target_agreements
(
	id serial not null
		constraint target_agreements_pk
			primary key,
	name varchar,
	concluded_with varchar,
	abit_id integer not null
		constraint target_agreements_abiturients_id_fk
			references abiturients
);

alter table target_agreements owner to postgres;

create unique index target_agreements_id_uindex
	on target_agreements (id);

create table wo_compet
(
	id serial not null
		constraint wo_compet_pk
			primary key,
	name varchar not null,
	type varchar,
	given_by varchar,
	abit_id integer not null
		constraint wo_compet_abiturients_id_fk
			references abiturients
);

alter table wo_compet owner to postgres;

create unique index wo_compet_id_uindex
	on wo_compet (id);

create table exams
(
	id serial not null
		constraint exams_pk
			primary key,
	subject_id integer
		constraint exams_exam_subjects_id_fk
			references exam_subjects,
	points integer,
	abit_id integer
		constraint exams_abiturients_id_fk
			references abiturients
);

alter table exams owner to postgres;

create unique index exams_id_uindex
	on exams (id);

create table adresses
(
	id serial not null
		constraint registrations_pk
			primary key,
	abit_id integer
		constraint registrations_abiturients_id_fk
			references abiturients,
	county varchar,
	city varchar,
	street varchar,
	house varchar,
	apartment varchar,
	is_current_living boolean default false,
	post_index varchar,
	fias varchar
);

alter table adresses owner to postgres;

create unique index registrations_id_uindex
	on adresses (id);

create unique index campaign_id_uindex
	on campaign (id);

create table certificates
(
	id serial not null
		constraint certificates_pk
			primary key,
	abit_id integer
		constraint certificates_abiturients_id_fk
			references abiturients
				on update cascade,
	given_by varchar,
	date date,
	is_red boolean default false,
	type varchar,
	education_level integer
);

alter table certificates owner to postgres;

create unique index certificates_id_uindex
	on certificates (id);

create table abit_achievements
(
	abit_id integer not null
		constraint abit_achievements_pk_2
			primary key
		constraint abit_achievements_abiturients_id_fk
			references abiturients,
	achievement_id integer
		constraint abit_achievements_pk
			unique
		constraint abit_achievements_achievements_code_fk
			references achievements
);

alter table abit_achievements owner to postgres;

create table applications
(
	id serial not null
		constraint applications_pk
			primary key,
	abit_id integer
		constraint applications_abiturients_id_fk
			references abiturients,
	is_agreed boolean default false,
	date date,
	spec_id integer
		constraint applications_specialities_id_fk
			references specialities,
	campaign_id integer
		constraint applications_campaign_id_fk
			references campaign
);

alter table applications owner to postgres;

create unique index applications_id_uindex
	on applications (id);

create table spec_subjects
(
	spec_id integer not null
		constraint spec_subjects_specialities_id_fk
			references specialities,
	subject_id integer not null
		constraint spec_subjects_exam_subjects_id_fk
			references exam_subjects,
	pass_points integer,
	constraint spec_subjects_pk
		primary key (spec_id, subject_id)
);

alter table spec_subjects owner to postgres;

create table credited_applications
(
	application_id integer not null
		constraint credited_applications_applications_id_fk
			references applications,
	order_id integer not null
		constraint credited_applications_orders_id_fk
			references orders,
	constraint credited_applications_pk
		primary key (application_id, order_id)
);

alter table credited_applications owner to postgres;

